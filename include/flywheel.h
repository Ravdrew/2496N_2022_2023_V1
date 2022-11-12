#include "main.h"
#include "robot.h"
#ifndef FLY_H_
#define FLY_H_

#define FLYWHEEL_SPEED_TARGET 385
#define SINGLE_SPEED_TARGET 373

int sgn(double input);
//void changeTBHTarget(float speed);
//void takeBackHalf();
void flywheelMove(double speed);
void flywheelBrake();
void changeFlywheelTarget(double speed);
void flywheelPDF();
void autonFlywheelPDF();
double getFlywheelTarget();

#endif
