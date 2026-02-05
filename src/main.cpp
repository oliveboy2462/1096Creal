// THIS IS A BASIC OPERATOR CONTROL SYSTEM

// Include Necessary Libraries
#include "main.h"
#include "autons.hpp"

int printNumber = 13;
// c++ doesn't like it when you change variables so no extern, but they already
// know there is a global variable
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"
#include <cstdlib>
#include <vector>
// Create Left and Right Motor sets on the drivetrain, set to negative to
// reverse motors
pros::MotorGroup left_motors({1, 9}, pros::MotorGearset::blue);
pros::MotorGroup right_motors({-2, -10}, pros::MotorGearset::blue);
// Create a Drivetrain Object
lemlib::Drivetrain drivetrain(&left_motors,  // left motor group
                              &right_motors, // right motor group
                              13,            // ~10 inch track width
                              lemlib::Omniwheel::NEW_4,
                              360, // drivetrain rpm is 400
                              2    // horizontal drift is 2
);
pubFunctions fncts; // calls the object auton and duplicate it with another name
                    // (ctrl f fncts to find usage)

// Initialize odomerty sensors, in this case only an IMU
lemlib::OdomSensors
    sensors(nullptr, // vertical tracking wheel 1, set to nullptr
            nullptr, // vertical tracking wheel 2
            nullptr, // horizontal tracking wheel 1
            nullptr, // horizontal tracking wheel 2
            nullptr  // imu
    );

// Once everything is done, this is just a guess and check, don't touch integral
// gain really tho' lateral PID controller
lemlib::ControllerSettings
    lateral_controller(20,  // proportional gain (kP)
                       0,   // integral gain (kI)
                       80,  // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in inches
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in inches
                       500, // large error range timeout, in milliseconds
                       20   // maximum acceleration (slew)
    );

// angular PID controller
lemlib::ControllerSettings
    angular_controller(4,   // proportional gain (kP)
                       0,   // integral gain (kI)
                       29,  // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in degrees
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in degrees
                       500, // large error range timeout, in milliseconds
                       0    // maximum acceleration (slew)
    );
// create the chassis Object
lemlib::Chassis chassis(drivetrain,         // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors             // odometry sensors
);

// Create Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

/**                                                                            \
 * Runs initialization code. This occurs as soon as the program is started.    \
 *                                                                             \
 * All other competition modes are blocked by initialize; it is recommended    \
 * to keep execution time for this mode under a few seconds.                   \
 */
// Make sure bot is ready
void initialize() {
  chassis.calibrate(true);
  // Initialize chassis and macros
  master.rumble(".");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
// Why would we need this
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
// Useless
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.j
 */
void autonomous() {
  // lemlib::Pose set_Pose(1, 2, 3);
  // Set the break mode for the autonomous
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
  fncts.moveToGoal("Red Right", "Right", "set");
  fncts.moveToGoal("Red Lower Points", "Right", "goal");
  fncts.moveToGoal("Red Lower Goal", "Right", "goal");
  fncts.moveToGoal("Red Park", "Middle", "goal");
  fncts.autonIntake("In");
  fncts.autonConveyor("In");
  pros::delay(400);
  fncts.autonIntake("Out");
  fncts.autonConveyor("Out");

  // run auton selector,
  // watch code implode

  // Run specific auton, uncomment used Auton, NOTICE, this is the MAIN file,
  // not the AUTON file, once you get to this point, I can teach you how to
  // integrate multiple files together autons_positive_red();
  // autons_positive_blue();
  //  autons_negative_red();
  // autons_negative_blue();
}
// Curve stuff good, no touch
lemlib::ExpoDriveCurve throttle(3, 12, 1.05);
lemlib::ExpoDriveCurve steerCurve(3, 12, 1.05);

// Definitions to make some stuff easier
namespace pros {
#define E_CONTROLLER_DIGITAL_L0 E_CONTROLLER_DIGITAL_RIGHT
#define E_CONTROLLER_DIGITAL_R0 E_CONTROLLER_DIGITAL_Y
} // namespace pros

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {

  // Sets the brake mode
  pros::motor_brake_mode_e_t driver_preference_brake =
      pros::E_MOTOR_BRAKE_COAST;
  chassis.setBrakeMode(driver_preference_brake);

  // Iteration counter if you want to do timing stuff
  int iteration = 0;
  while (true) {
    // fncts.printANumber(1,1,1); //find printANumber in fncts

    //  Get how far the joysticks are moved
    int leftY = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    int rightY = (master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    // make it TENK with the joysticks
    chassis.tank(leftY, rightY);
    fncts.intakeFunc();
    fncts.conveyorFunc();
    // fncts.speedControl(pros::MotorGroup({1, 9}, pros::MotorGearset::blue),
    // pros::MotorGroup({2, 10}, pros::MotorGearset::blue));

    // delay a small amount to prevent brain overload and improve timer
    // accuracy
    pros::delay(10); // Timer calculations and not making the brain into a
                     // fusion reactior
    iteration++;
    // std::cout<<iteration<<"\n";
  }
}
