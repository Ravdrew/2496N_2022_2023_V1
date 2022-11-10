#include "main.h"
#include "robot.h"
#include "movement.h"
#include "flywheel.h"
#include "autons.h"
#include <cmath> //keijay added this, it makes our code look cooler...
 
void AWP(){
    changeFlywheelTarget(432);
    pros::Task autoFlyControl(flywheelPDF);
    intake.move(-60);
    timedMove(-50,100);
    pros::delay(1250);
    shootDisks(2);
    pros::delay(100);
    move(330);
    flywheelMove(0);
    intake.move(100);
    pros::delay(500);
    absturn(-123, false);
    move(-1350, false, 0, 120, 1800);
    intake.move(75);
    pros::delay(500);
    move(-150, false, 0, 20, 500);
    // pros::delay(500);
    // flywheelMove(455);
    // move(-1190, false, 0, 60, 1400);
    // absturn(-25, false);
    // intake.move(0);
    // shootDisks(4);
    // flywheelMove(0);
    // absturn(-132, false);
    // intake.move(-127);
    // move(-2400);
 
}
 
void taivexautoncount(){
    flywheelMove(475); //moves flywheel at 475 rpm to rev it up
    intake.move(-70); // intakes move
    timedMove(-80, 300);
    move(330);
    intake.move(0);
    pros::delay(700);
   
 
 
}
 
void rollerSide(){
    flywheelMove(460);
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
    flywheelMove(435);
    absturn(-23, false);
    pros::delay(500);
    intake.move(0);
    shootDisks(3);
}
 
void offSideRoller(){
    flywheelMove(470);
    move(-1400);
    absturn(90);
    intake.move(-70);
    timedMove(-80,300);
    //pros::delay(50);
    move(330);
    absturn(104);
    shootDisks(2);
    flywheelMove(0);
    intake.move(0);
}
 
void rollerOnly(){
    intake.move(-70);
    timedMove(-80,300);
    //pros::delay(50);
    move(330);
}
 
void noAuton(){
    intake.move(-70);
    timedMove(-80,300);
    //pros::delay(50);
    move(330);
}
 
void skills(){
   
}
 
