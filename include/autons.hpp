#pragma once
// include for every hpp
//  included only once during a single compilation. This prevents issues like
//  multiple definition errors
// that can arise when the same header file is included more than once in a
// translation unit.
#include "algorithm"
#include "iostream"
#include "list"
#include "main.h"
#include <string>

// ig it includes where you can check for functions and values
// says that there is a void function somewhere

extern int printNumber;
class pubFunctions { // makes an object called auton
public: // public information: implied what it does there is also an opposite
        // called private:
  void function();
  void printANumber(float x, float y, float theta);
  void moveToGoal(std::string Goal, std::string Quadrant);
  void opControl();
  void speedControl(pros::MotorGroup leftGroup, pros::MotorGroup rightGroup);
  void intakeFunc();
  void autonIntake(std::string inOrOut);
  void conveyorFunc();
  void autonConveyor(std::string inOrOut);
  // void conveyorFunc();
};

class variablesAndLists {
public:
  std::list<std::string> autonPlaces{"Starting",
                                     "Park",
                                     "Middle Goal",
                                     "Middle Corners",
                                     "Halfway to Other Side",
                                     "Match Load",
                                     "Long Goal"};
  std::string quad = "Left";
};