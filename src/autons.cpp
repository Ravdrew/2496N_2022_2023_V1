#include "main.h"
#include "robot.h"
#include "movement.h"
#include "flywheel.h"
#include "autons.h"
#include <cmath> //keijay added this, it makes our code look cooler...
 
void AWP(){
    changeFlywheelTarget(590);
    pros::Task autoFlyControl(autonFlywheelPDF);
    intake.move(-60);
    timedMove(-50,150);
    pros::delay(1200);
    shootDisks(2);
    //pros::delay(100);
    move(330);
    changeFlywheelTarget(-5);
    intake.move(70);
    pros::delay(400);
    absturn(-123, false);
    move(-1700, false, 0, 90, 2000);
    intake.move(127);
    //pros::delay(100);
    move(-1300, false, 0, 50, 1800);
    changeFlywheelTarget(490);
    absturn(-27, false);

    //pros::delay(1000);
    shootDisks(3);
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
    changeFlywheelTarget(540);
    pros::Task autoFlyControl(autonFlywheelPDF);
    move(-1600);
    absturn(90);
    pros::delay(300);
    intake.move(-90);
    timedMove(-127,360);
    //pros::delay(50);
    move(330);
    intake.move(0);
    absturn(105);
    shootDisks(2);
    /*pros::delay(200);
    changeFlywheelTarget(-5);
    pros::delay(250);
    absturn(218, false);
    intake.move(127);
    move(-3300, false, 0, 100, 2000);
    changeFlywheelTarget(495);
    //changeFlywheelTarget(486);
    pros::delay(1000);
    absturn(137, false);
    shootDisks(3);
    
    
    //flywheelMove(0);
    //intake.move(0);
    //absturn(20);*/
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
 
