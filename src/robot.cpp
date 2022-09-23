#include "main.h"
#include "robot.h"
#include "piston.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);//gu
pros::Motor leftFront(5, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(6, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFront(20, MOTOR_GEARSET_6, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(4, MOTOR_GEARSET_6, true, MOTOR_ENCODER_DEGREES); 
pros::Motor intake(15, MOTOR_GEARSET_6, true, MOTOR_ENCODER_DEGREES);
pros::Motor indexer(17, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::Motor midFlywheel(11, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::Motor outFlywheel(16, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

pros::Optical optical_sensor(8);
pros::c::optical_rgb_s_t rgb_value;
// pros::Limit limit_sensor(10);

pros::ADIEncoder leftE(1, 2);
pros::ADIEncoder rightE(3, 4);
pros::ADIEncoder midE(7, 8);

Piston end_game_left(5);

pros::Imu imu(8);

void reset_encoders(){
    leftFront.tare_position();
	leftBack.tare_position();
	rightFront.tare_position();
	rightBack.tare_position();
}