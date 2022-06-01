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
void goalYoink();
void goalYoinkLeft();
void goalYoinkMid();
void postGoalReset();
void turn(int target, bool ask_slew = false, int slew_rate = 0);
void absturn(int abstarget, bool ask_slew = true, int slew_rate = 9, int power_cap = 127);
void absturnTimed(int abstarget, int timer_amt = 80, bool ask_slew = false, int slew_rate = 0, int power_cap = 127);

void chainClawOpen();
void chainClawClose();
void jsClawOpen();
void jsClawClose();
void stickDown();
void stickUp();
void hoodOpen();
void hoodClose();

extern float start_heading;
extern bool openChain;
extern bool openJS;
extern bool openStick;
extern bool openHood;

void moveTillChain(int speed, int timer = 300);
void moveTillJS(int speed, int timer = 300);

/*void scooperTurnTo(int target, int speed);
void scooperDropRing(void * param);
void scooperSetLow(void * param);
void scooperHoldUp(void * param);
void scooperSetLowLimit();
void scooperReturn(void * param);
void scooperReturnSlow(void * param);
void liftTurnTo(int target, int speed);
void liftSetLow(void * param);
void liftSetHigh(void * param);
void scooperDropGoal(void * param);*/

#endif
