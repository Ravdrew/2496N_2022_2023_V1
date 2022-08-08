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
extern pros::Motor midFlywheel; //4
extern pros::Motor outFlywheel; //10

extern pros::ADIEncoder leftE;
extern pros::ADIEncoder rightE;
extern pros::ADIEncoder midE;

extern pros::Optical optical_sensor;
extern pros::c::optical_rgb_s_t rgb_value;

extern pros::Imu imu;
extern pros::ADIDigitalOut chainClaw;
extern pros::ADIDigitalOut jSClamp;
extern pros::ADIDigitalOut stick;
extern pros::ADIDigitalOut hood;

void reset_encoders();

#endif