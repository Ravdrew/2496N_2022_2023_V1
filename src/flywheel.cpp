#include "main.h"
#include "robot.h"
#include "flywheel.h"
#include <stdio.h>
#include <vector>
 
#define TBH_GAIN 0
#define F_KP 0.9
#define F_KI 0.0
#define F_KD 0
#define F_KF 0.213
#define ENCODER_TO_ROTATION 0
#define MINUTE_IN_MILLISECOND 60000.0
#define EMA_ALPHA 0.3

void flywheelMove(double speed){
    outFlywheel.move(speed);
	midFlywheel.move(speed);
}

void flywheelBrake(){
    outFlywheel.brake();
	midFlywheel.brake();
}

int sgn(double input){
	return input/abs(input);
}

double EMA(double alpha, double latest, double stored){
    return alpha*latest + (1-alpha)*stored;
}


double f_time = 0;
double f_error = 0;
double f_prev_error = 0;
double f_derivative = 0;
double f_power = 0;
double f_output = 0;
double f_target = FLYWHEEL_SPEED_TARGET;
double f_curr_speed;

double ema_result;
double prev_ema_result = 0;

double dema_result;

double f_input;

bool fileCreated = false;

//you are hot
void changeFlywheelTarget(double speed){
    f_target = speed;
}

double getFlywheelTarget(){
    return f_target;
}

void flywheelPDF(){      
    f_curr_speed = (midFlywheel.get_actual_velocity() + outFlywheel.get_actual_velocity()) / 2;

    ema_result = EMA(EMA_ALPHA, f_curr_speed, ema_result);
    //dema_result = 2*ema_result - EMA(EMA_ALPHA, ema_result, dema_result);
    
    f_input = ema_result;

    f_prev_error = f_error;
    f_error = f_target - f_input;

    f_derivative = f_error - f_prev_error; 

    f_output = F_KP * f_error + F_KD * f_derivative + F_KF * f_target;

    flywheelMove(f_output);

    float f_draw = midFlywheel.get_voltage() + outFlywheel.get_voltage();


    std::cout << f_time << " " << f_curr_speed << " " << ema_result << " " << dema_result << " " << f_output << " " << f_draw << "\n";

    f_time += 10;
}

/*float tbh_target = 600;

float tbh_error = 0;
float tbh_prev_error = 0;

float tbh_curr_speed;
float tbh_output = 0;

float tbh_tbh = 0;

void changeTBHTarget(float speed){
    tbh_target = speed;
}

void takeBackHalf(){
    tbh_curr_speed = (midFlywheel.get_actual_velocity() + outFlywheel.get_actual_velocity())/2;

    tbh_error = tbh_target - tbh_curr_speed;
    tbh_output += TBH_GAIN * tbh_error;
    if (sgn(tbh_error) != sgn(tbh_prev_error)) {
        tbh_output = 0.5 * (tbh_output + tbh_tbh);
        tbh_tbh = tbh_output;
    }
    tbh_prev_error = tbh_error;

    midFlywheel.move(tbh_output);
    outFlywheel.move(tbh_output);
}*/