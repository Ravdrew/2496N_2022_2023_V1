#include "main.h"
#include "robot.h"
#include "movement.h"
#include "flywheel.h"
#include "autons.h"

void AWP(){
    flywheelMove(0);
    intake.move(-70);
    timedMove(-80,300);
    //pros::delay(50);
    move(330);
    intake.move(0);
    absturn(-130, false);
    intake.move(-70);
    move(-1600);
    intake.move(127);
    flywheelMove(440);
    move(-1190, false, 0, 45, 1400);
    absturn(-25, false);
    intake.move(0);
    shootDisks(3);
    flywheelMove(0);
    absturn(-132, false);
    intake.move(-127);
    move(-2400);

}

void rollerSide(){
    flywheelMove(455);
    intake.move(-70);
    timedMove(-80,300);
    //pros::delay(50);
    move(330);
    intake.move(0);
    pros::delay(700);
    shootDisks(2);
    flywheelMove(0);
    absturn(-130, false);
    intake.move(-75);
    move(-1550);
    intake.move(127);
    move(-1140, false, 0, 30, 1400);
    flywheelMove(440);
    absturn(-23, false);
    pros::delay(500);
    intake.move(0);
    shootDisks(3);
}

void mid(){
    intake.move(-70);
    timedMove(-80,300);
    //pros::delay(50);
    move(330);
}

void noAuton(){}