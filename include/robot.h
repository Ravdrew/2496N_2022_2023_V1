#include "main.h"
#include "piston.h"

#ifndef ROBOT_H_
#define ROBOT_H_
extern pros::Controller controller;
extern pros::Motor leftFront; 
extern pros::Motor leftMid;
extern pros::Motor leftBack;
extern pros::Motor rightFront; 
extern pros::Motor rightMid;
extern pros::Motor rightBack;
extern pros::Motor chainBar;
extern pros::Motor intake;
extern pros::Motor indexer;
extern pros::Motor midFlywheel;
extern pros::Motor outFlywheel;

extern Piston endBack;
extern Piston intakePiston;

extern pros::Imu imu;

extern pros::ADIPotentiometer pot;

extern pros::ADIAnalogIn lineFollower;


void reset_encoders();

#endif