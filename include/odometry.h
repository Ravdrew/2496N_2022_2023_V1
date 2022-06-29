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
/*#define TICKS_PER_REV 360
#define WHEEL_DIA 2.758*/
#define ENC_TO_INCH 2.75*3.14159265358979323846/360

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

    dX = cos(rotationCenter) * dXR − sin(rotationCenter) * dYR;
    dY = sin(rotationCenter) * dXR + cos(rotationCenter) * dYR;

    abs_x += dX;
    abs_y += dY;
}

#endif
