#include "main.h"
#include "robot.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor leftFront(14, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor leftMid(12, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES); //kinda not good
pros::Motor leftBack(11, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightFront(19, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightMid(18, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(17, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor chainBar(2, MOTOR_GEARSET_36, true , MOTOR_ENCODER_DEGREES); //Gerald waz here
pros::Motor intake(1, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

pros::Imu imu(8);
pros::ADIDigitalOut chainClaw(1);
pros::ADIDigitalOut jSClamp(2);
pros::ADIDigitalOut stick(8);
pros::ADIDigitalOut hood(6);

void reset_encoders(){
    leftFront.tare_position();
	leftMid.tare_position();
	leftBack.tare_position();
	rightFront.tare_position();
	rightMid.tare_position();
	rightBack.tare_position();
}