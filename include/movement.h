#include "main.h"
#include "robot.h"
#include "PID.h"
#ifndef MOVEMENT_H_
#define MOVEMENT_H_

//extern bool autonOn;

void chas_move(int left_power, int right_power);
void quickie(int target, bool claw = false);
void move(int target, bool ask_slew = false, int slew_rate = 0, int power_cap = 127, int active_cap = 0);
void moveTimed(int target, int timer_amt = 80);
void turn(int target, bool ask_slew = false, int slew_rate = 0);
void absturn(int abstarget, bool ask_slew = true, int slew_rate = 9, int power_cap = 127);
void absturnTimed(int abstarget, int timer_amt = 80, bool ask_slew = false, int slew_rate = 0, int power_cap = 127);

extern float start_heading;

#endif
