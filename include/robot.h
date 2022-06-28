#include "main.h"

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
extern pros::Motor leftFlywheel; //4
extern pros::Motor rightFlywheel; //10

extern pros::Imu imu;
extern pros::ADIDigitalOut chainClaw;
extern pros::ADIDigitalOut jSClamp;
extern pros::ADIDigitalOut stick;
extern pros::ADIDigitalOut hood;

void reset_encoders();

#endif