#include "autons.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
// pros mu is the upload and build command
pros::Controller masterController(pros::E_CONTROLLER_MASTER);
pros::Motor leftIntake(3);
pros::Motor rightIntake(7);
// port 8 and 15 cannot be used
pros::Motor conveyorMotor(4);
// pros::Motor conveyor(4);
int intakeSpeed = 127;
// int printNumber = 5;
int velocity = 100;
void pubFunctions::moveToGoal(std::string Goal, std::string Quadrant) {
  float goalX = 0;
  float goalY = 0;
  float goalT = 90;
  if (Goal == "Starting") {
    goalX = 48;
    if (Quadrant != "Middle") {
      goalX = 64;
      goalY = 17;
    }
  } else if (Goal == "Park") {
    goalX = 64;
  } else if (Goal == "Middle Goal") {
    goalX = 12;
    goalY = 12;
    goalT = 45;
  } else if (Goal == "Middle Corners") {
    goalX = 23;
    goalY = 23;
  } else if (Goal == "Halfway to Other Side") {
    goalX = 35;
    goalY = 23;
    goalT = 180;
  } else if (Goal == "Match Load") {
    goalX = 60; // 60
    goalY = 45; // 45
    goalT = 270;
  } else if (Goal == "Long Goal") {
    goalX = 30;
    goalY = 45;
  } else {
    std::cout << "what goal?" << "\n";
    pros::lcd::print(4, "what goal?");
  }
  goalX = -goalX;
  goalY = -goalY;
  if (Quadrant == "Left") {
    goalY = -goalY;
    if (goalT != 270) {
      goalT = 90 - (goalT - 90);
    }
  }

  chassis.moveToPose(goalX, goalY, goalT, 3000);
  pros::lcd::print(3, "what goal done");
  // std::cout << Goal << "\n";

  // pros::delay(350);
};

void pubFunctions::printANumber(float x, float y, float theta) {
  std::cout << "coordinates are: " << x << ", " << y << ", " << theta << "\n";
  std::cout << printNumber << "\n";
  printNumber = 10;
  pros::delay(10);
};

void moveToTopCenterGoal() {
  // chassis.setPose(startPos);
  chassis.moveToPose(-17, 18, 135, 5000);
}

void moveToThis(float x, float y, float theta) {
  lemlib::Pose goal(x, y, theta);
};

// int conveyorSpeed = 130;
// look at the motor is clockwise positive velocities are clockwise and opposite
// is anti (-127 - 127)
void pubFunctions::intakeFunc() {
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    leftIntake.move_velocity(intakeSpeed);
    rightIntake.move_velocity(-intakeSpeed);
  } else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    leftIntake.move_velocity(-intakeSpeed);
    rightIntake.move_velocity(intakeSpeed);
  } else {
    leftIntake.move_velocity(0);
    rightIntake.move_velocity(0);
  }
  pros::delay(100);
};

void pubFunctions::autonIntake(std::string inOrOut) {
  if (inOrOut == "In") {
    leftIntake.move_velocity(intakeSpeed);
    rightIntake.move_velocity(-intakeSpeed);
  } else if (inOrOut == "Out") {
    leftIntake.move_velocity(-intakeSpeed);
    rightIntake.move_velocity(intakeSpeed);
  } else if (inOrOut == "Stop") {
    leftIntake.move_velocity(0);
    rightIntake.move_velocity(0);
  }
}

void pubFunctions::conveyorFunc() {
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    conveyorMotor.move_velocity(-intakeSpeed);
    std::cout << "conveyor" << "\n";
  } else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    conveyorMotor.move_velocity(intakeSpeed);
  } else {
    conveyorMotor.move_velocity(0);
  }
}

void pubFunctions::autonConveyor(std::string inOrOut) {
  if (inOrOut == "In") {
    conveyorMotor.move_velocity(-intakeSpeed);
  } else if (inOrOut == "Out") {
    conveyorMotor.move_velocity(intakeSpeed);
  } else if (inOrOut == "Stop") {
    conveyorMotor.move_velocity(0);
  }
}
// void pubFunctions::conveyorFunc() {
//   if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
//     conveyor.move_velocity(conveyorSpeed);
//   } else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
//     conveyor.move_velocity(-conveyorSpeed);
//   }
//   pros::delay(1000);
// }
//* void pubFunctions::speedControl(pros::MotorGroup leftGroup,
//                      pros::MotorGroup rightGroup) {
//  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
