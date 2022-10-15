#include "main.h"
#include "robot.h"
#include "movement.h"
#include "flywheel.h"
#include "autons.h"

void AWP(){
    intake.move(-50);
    timedMove(-60, 60);
    //pros::delay(50);
    move(350);
    intake.move(0);
    absturn(-130, false);
    intake.move(-80);
    move(-1480);
    intake.move(127);
    move(-900, false, 0, 20, 1400);
    flywheelMove(440);
    absturn(-22, false);
    intake.move(0);
    pros::delay(2000);
    shootDisks(3);
}

void rollerSide(){

}

void mid(){

}

void noAuton(){}