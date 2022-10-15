#include "main.h"
#include "robot.h"
#include "movement.h"
#include "autons.h"

void AWP(){
    intake.move(-60);
    timedMove(-60, 95);
    //pros::delay(50);
    move(350);
    intake.move(0);
    absturn(-130, false);
    intake.move(127);
    
}

void rollerSide(){

}

void mid(){

}

void noAuton(){}