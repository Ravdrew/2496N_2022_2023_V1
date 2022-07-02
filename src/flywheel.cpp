#include "main.h"
#include "robot.h"
#include "flywheel.h"
#define TBH_GAIN 0

int sgn(double input){
	return input/abs(input);
}

float tbh_target = 600;

float tbh_error = 0;
float tbh_prev_error = 0;

float tbh_curr_speed;
float tbh_output = 0;

float tbh_tbh = 0;

void changeTBHTarget(float speed){
    tbh_target = speed;
}

void takeBackHalf(){
    tbh_curr_speed = (leftFlywheel.get_actual_velocity() + rightFlywheel.get_actual_velocity())/2;

    tbh_error = tbh_target - tbh_curr_speed;
    tbh_output += TBH_GAIN * tbh_error;
    if (sgn(tbh_error) != sgn(tbh_prev_error)) {
        tbh_output = 0.5 * (tbh_output + tbh_tbh);
        tbh_tbh = tbh_output;
    }
    tbh_prev_error = tbh_error;

    leftFlywheel.move(tbh_output);
    rightFlywheel.move(tbh_output);
}