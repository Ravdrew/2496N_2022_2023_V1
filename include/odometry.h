#include "main.h"
#include "robot.h"
#include <cmath>

#ifndef ODOM_H_
#define ODOM_H_
#define LDC 0
#define RDC 0
#define MDC 0
#define DEG_TO_RAD 3.14159265358979323846/180
#define RAD_TO_DEG 180/3.14159265358979323846
#define TICKS_PER_REV 360
#define WHEEL_DIA 2.758
#define ENC_TO_INCH 2.75*3.14159265358979323846/360

#define RED_GOAL_X 0
#define RED_GOAL_Y 0

#define BLUE_GOAL_X 0
#define BLUE_GOAL_Y 0

bool red = true;

double abs_x = 0;
double abs_y = 0;
double abs_ang = 0;

double prev_ang = 0;

double start_ang = 0;

double rotationCenter = 0;

double prevL = 0;
double prevR = 0;
double prevM = 0;

double currL = 0;
double currR = 0;
double currM = 0;

double dL = 0;
double dR = 0;
double dM = 0;
double dAng = 0;

double dXR = 0;
double dYR = 0;

double dX = 0;
double dY = 0;

void prepOdom(float a_start_x, float a_start_y, float a_start_ang){
    abs_x = a_start_x;
    abs_y = a_start_y;
    start_ang = a_start_ang;
}

void odometry(){
    prevL = currL;
    prevR = currR;
    prevM = currM;
    prev_ang = abs_ang;

    currL = leftE.get_value()*ENC_TO_INCH;
    currR = rightE.get_value()*ENC_TO_INCH;
    currM = midE.get_value()*ENC_TO_INCH;

    dL = currL - prevL;
    dR = currR - prevR;
    dM = currM - prevM;

    abs_ang = start_ang + (dL - dR)/(LDC + RDC);

    dAng = abs_ang - prev_ang;

    if(dAng == 0){
        dXR = dM;
        dYR = dR;
    }
    else{
        dXR = 2*sin(dAng/2) * (dM/dAng + MDC);
        dYR = 2*sin(dAng/2) * (dR/dAng + RDC);
    }

    rotationCenter = -1*(prev_ang + ((dL - dR)/(LDC + RDC))/2);

    dX = cos(rotationCenter) * dXR - sin(rotationCenter) * dYR;
    dY = sin(rotationCenter) * dXR + cos(rotationCenter) * dYR;

    abs_x += dX;
    abs_y += dY;
}

void callibration(){
    controller.print(1,0,"X: %f\n     ", abs_x);
    controller.print(2,0,"Y: %f\n     ", abs_y);
    controller.print(3,0,"ang: %f\n     ", abs_ang);
}

float getX(){
    return abs_x;
}

float getY(){
    return abs_y;
}

float getAng(){
    return abs_ang;
}

float distToGoal(bool red){
    if(red) return sqrt(pow(abs_x - RED_GOAL_X,2) + pow(abs_y - RED_GOAL_Y,2));
    return sqrt(pow(abs_x - BLUE_GOAL_X,2) + pow(abs_y - BLUE_GOAL_Y,2));
}

float angToGoal(bool red){
    if(red) return atan((abs_y - RED_GOAL_Y) / (abs_x - RED_GOAL_X)) * RAD_TO_DEG;
    return atan((abs_y - BLUE_GOAL_Y) / (abs_x - BLUE_GOAL_X)) * RAD_TO_DEG;
}

#endif

