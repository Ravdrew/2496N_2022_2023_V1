#include "main.h"
#include "robot.h"
#ifndef FLY_H_
#define FLY_H_

#define FLYWHEEL_SPEED_TARGET 385
int sgn(double input);
//void changeTBHTarget(float speed);
//void takeBackHalf();
void flywheelMove(double speed);
void flywheelBrake();
void changeFlywheelTarget(double speed);
void flywheelPDF();

#endif
