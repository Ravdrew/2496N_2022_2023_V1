#include "main.h"
#include "robot.h"
#include "PID.h"
#ifndef MOVEMENT_H_
#define MOVEMENT_H_

//extern bool autonOn;

void chas_move(int left_power, int right_power);
void quickie(float target);
void move(float target, bool ask_slew = false, float slew_rate = 0, float power_cap = 127, float active_cap = 0);
void moveTimed(float target, int timer_amt = 80);
void turn(float target, bool ask_slew = false, float slew_rate = 0);
void absturn(float abstarget, bool ask_slew = true, float slew_rate = 9, float power_cap = 127);
void absturnTimed(float abstarget, int timer_amt = 80, bool ask_slew = false, float slew_rate = 0, float power_cap = 127);
void shootDisks(int num);
void timedMove(int speed, int time);

extern float start_heading;

#endif
