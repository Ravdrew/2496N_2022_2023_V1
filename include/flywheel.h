#include "main.h"
#include "robot.h"
#ifndef FLY_H_
#define FLY_H_

extern double f_target;

int sgn(double input);
//void changeTBHTarget(float speed);
//void takeBackHalf();
void flywheelMove(double speed);
void flywheelBrake();
void flywheelPDF();

#endif
