#include "main.h"
#include "robot.h"
#include "movement.h"
#include "autons.h"

void AWP(){
    //move(1500, true, 6);
    intake.move(127);
    pros::delay(500);
    intake.move(0);
}

void rollerSide(){

}

void mid(){

}

void noAuton(){}