#include "main.h"
#include "robot.h"
#ifndef FLY_H_
#define FLY_H_

#define FLYWHEEL_SPEED_TARGET 380
#define SINGLE_SPEED_TARGET 365

int sgn(double input);
//void changeTBHTarget(float speed);
//void takeBackHalf();
void flywheelMove(double speed);
void flywheelBrake();
void changeFlywheelTarget(double speed);
void flywheelPDF();
double getFlywheelTarget();

#endif
