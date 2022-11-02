#include "robot.h"
#include "piston.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);//gu
pros::Motor leftFront(16, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(17, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFront(19, MOTOR_GEARSET_6, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(18, MOTOR_GEARSET_6, true, MOTOR_ENCODER_DEGREES); 
pros::Motor intake(13, MOTOR_GEARSET_6, true, MOTOR_ENCODER_DEGREES);
pros::Motor indexer(20, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor midFlywheel(3, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);
pros::Motor outFlywheel(1, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

/*pros::Optical optical_sensor(8);
pros::c::optical_rgb_s_t rgb_value;*/
// pros::Limit limit_sensor(10);

pros::ADIAnalogIn lineFollower (6);

/*pros::ADIEncoder leftE(1, 2);
pros::ADIEncoder rightE(3, 4);*/
//pros::ADIEncoder midE(7, 8);

Piston endBack(7);
Piston intakePiston(8);

pros::ADIPotentiometer pot (3, pros::E_ADI_POT_V2);

pros::Imu imu(15);

void reset_encoders(){
    leftFront.tare_position();
	leftBack.tare_position();
	rightFront.tare_position();
	rightBack.tare_position();
}