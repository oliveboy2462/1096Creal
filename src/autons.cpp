#include "autons.hpp"
#include "lemlib/pose.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"

// int printNumber = 5;
int velocity = 100;
void pubFunctions::moveToGoal(std::string Goal, std::string type) {
  float goalX = 32;
  float goalY = 47.5;
  float goalT;
  float setX = 64;
  float setY = 20;
  float setT;
  if (Goal == "Red Left") {
    goalX = -goalX;
    goalY = goalY;
    goalT = 270;
    setX = -setX;
    setY = setY;
    setT = 90;
  } else if (Goal == "Red Right") {
    goalX = -goalX;
    goalY = -goalY;
    goalT = 270;
    setX = -setX;
    setY = -setY;
    setT = 90;
  } else if (Goal == "Blue Left") {
    goalX = goalX;
    goalY = -goalY;
    goalT = 90;
    setX = setX;
    setY = -setY;
    setT = 270;
  } else if (Goal == "Blue Right") {
    goalX = goalX;
    goalY = goalY;
    goalT = 90;
    setX = setX;
    setY = setY;
    setT = 270;
  } else if (Goal == "Red Lower Goal") {
    goalX = 40;
    goalY = 40;
    goalT = 45;
  } else if (Goal == "Red Lower Points") {
    goalX = -60;
    goalY = -60;
    goalT = 90;
  } else if (Goal == "Red Park") {
    goalX = -165;
    goalY = 0;
    goalT = 90;
  } else {
    std::cout << "what goal?" << "\n";
  }
  if (type == "beginning" || type == "set") {
    chassis.setPose(lemlib::Pose(setX, setY, setT));
  }
  if (type == "beginning" || type == "goal") {
    chassis.moveToPose(goalX, goalY, goalT, 5000);
  }
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

pros::Controller masterController(pros::E_CONTROLLER_MASTER);
pros::Motor leftIntake(3);
pros::Motor rightIntake(8);
pros::Motor conveyor(4);
int intakeSpeed = 127;
int conveyorSpeed = 130;
// look at the motor is clockwise positive velocities are clockwise and opposite
// is anti (-127 - 127)
void pubFunctions::intakeFunc() {
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    leftIntake.move_velocity(intakeSpeed);
    rightIntake.move_velocity(intakeSpeed);
  } else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    leftIntake.move_velocity(-intakeSpeed);
    rightIntake.move_velocity(-intakeSpeed);
  }
  pros::delay(1000);
};

void pubFunctions::conveyorFunc() {
  if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    conveyor.move_velocity(conveyorSpeed);
  } else if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    conveyor.move_velocity(-conveyorSpeed);
  }
  pros::delay(1000);
}
//* void pubFunctions::speedControl(pros::MotorGroup leftGroup,
//                     pros::MotorGroup rightGroup) {
// if (masterController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
