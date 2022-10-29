#include "main.h"
#include "robot.h"
#include "flywheel.h"
 
#define TBH_GAIN 0
#define F_KP 0
#define F_KI 0
#define F_KD 0
#define F_KF 0
#define ENCODER_TO_ROTATION 0
#define MINUTE_IN_MILLISECOND 60000.0

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

int f_time = 0;
double f_error = 0;
double f_prev_error = 0;
double f_derivative = 0;
double f_power = 0;
double f_output = 0;
double f_target = 600;
double f_prev_dist = 0;
double f_curr_dist = 0;
//you are hot

void flywheelPDF(){
    midFlywheel.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
    outFlywheel.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);

    double f_curr_speed = (f_curr_dist - f_prev_dist) / 10.0 * MINUTE_IN_MILLISECOND;
    //std::cout << (f_curr_dist - f_prev_dist) / 10.0 << std::endl;
    std::cout << "my speed: " << f_curr_speed << "      pros speed:" << (midFlywheel.get_actual_velocity() + outFlywheel.get_actual_velocity()) / 2 << std::endl;

    f_prev_error = f_error;
    f_error = f_target - f_curr_speed;

    f_derivative = f_error - f_prev_error; 

    f_output = F_KP * f_error + F_KD * f_derivative + F_KF * f_target;

    flywheelMove(127);

    f_time += 10;
    f_prev_dist = (midFlywheel.get_position() + outFlywheel.get_position()) / 2.0;
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