#include "main.h"
#include "robot.h"
#include "movement.h"
#include "PID.h"
#include "flywheel.h"
#include "autons.h"
#include <fstream>
#include <cmath>
#define OPTICAL_PORT 1
#define UP_MOST 23.0476
#define DOWN_MOST 111.451


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */

void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

// bool switchPressed = false;
bool resetNeeded = false;

int timer = 0;
int selectedAuto = 1;
int prevSelectedAuto = 1;


double curr_ang;

void competition_initialize() {
	controller.clear();
	while(true){
		prevSelectedAuto = selectedAuto;
		curr_ang = pot.get_angle();
		if(curr_ang > 5 && curr_ang < 75) selectedAuto = 1;
		else if (curr_ang >  80 && curr_ang < 150) selectedAuto = 2;
		else if(curr_ang > 155 && curr_ang < 225) selectedAuto = 3;
		else if(curr_ang > 235 && curr_ang  < 300) selectedAuto = 4;//while(Andres == "")
		else if(curr_ang > 300) selectedAuto = 0;

		//std::cout << "curr_ang: " << curr_ang << std::endl;
		//std::cout << "selected: " << selectedAuto << std::endl;

		if (!(timer % 5)) {
			switch(selectedAuto) {
				case 0:
					controller.print(1, 0, "NoA");
					break;
				case 1:
					controller.print(1, 0, "AWP");
					break;
				case 2:
					controller.print(1, 0, "Rol");
					break;
				case 3:
					controller.print(1, 0, "offSideRoller");
					break;
				case 4:
					controller.print(1,0, "Skills");
					break;
				default:
					controller.print(1, 0, "SEL");
			}
		}
		pros::delay(10);
		timer++;
	}
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
	start_heading = imu.get_rotation();
	switch(selectedAuto) {
		case 0:
			noAuton();
			break;
		case 1:
			AWP();
			break;
		case 2:
			rollerSide();
			break;
		case 3:
			offSideRoller();
			break;
		default:
			noAuton();
	}
	
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


/*
	1) fix vibrations
	2) add auton selector
*/
bool indexToggle = false;
bool skipStop = false;
double testFlywheelSpeed = FLYWHEEL_SPEED_TARGET;
bool rollerToggle = false;

void tripleShot(void* param){
	rollerToggle = true;
	intake.move(127);
	changeFlywheelTarget(600);
	indexer.move_relative(ONE_DISK_ROTATION*3, 121);
	pros::delay(700);
	changeFlywheelTarget(FLYWHEEL_SPEED_TARGET);
	indexToggle = false;
	intake.move(0);
	rollerToggle = false;
}

void singleShot(void* param){
	if(lineFollower.get_value() < 400 && lineFollower.get_value() > 0){
		skipStop = true;
	}
	//changeFlywheelTarget(600);
	indexer.move_relative(ONE_DISK_ROTATION, 170);
	pros::delay(250);
	//changeFlywheelTarget(FLYWHEEL_SPEED_TARGET);
	if(skipStop == false){
		indexToggle = false;//for 
	}
	else{
		skipStop = false;
	}
}


void opcontrol() {
	
	controller.clear();
	leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	indexer.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	outFlywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	midFlywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	int count = 0;
	int detectedTime = 0;
	bool intake_power = false;
	int intake_direction = 1;

	int selectedTeam = 1;
	double get_hue;
	bool flywheelAllowed = true;

	bool manualIndex = false;


	//changeFlywheelTarget(FLYWHEEL_SPEED_TARGET);

	
	while (true) {
		// if(controller.get_digital_new_press(DIGITAL_A)){
		// 	mid();
		// }
		//Selecting team for optical sensor
		

		if(!(count % 5)){
			//controller.print(0,1,"Blue %f");
			controller.print(0,0,"%f ", getFlywheelTarget());
		}

		// 	else if(selectedTeam == 1){
		// 		controller.print(0,1,"Red %f");
		// 		//controller.print(0,0,"%f ", (midFlywheel.get_actual_velocity() + outFlywheel.get_actual_velocity())/2);
		// 	}
		// }

		// //Optical Sensor Code
		

		// if (controller.get_digital_new_press(DIGITAL_L2)){
		// 	rollerToggle = !rollerToggle;
		// }
		// if(rollerToggle == true){
		// 	optical_sensor.set_led_pwm(100);
		// 	if(selectedTeam == -1){
		// 		intake.move(-127);
		// 		if(optical_sensor.get_hue() >= 100){
		// 			intake.brake();
		// 			rollerToggle = !rollerToggle;
		// 		}
		// 	}
		// 	else if(selectedTeam == 1){
		// 		intake.move(-127);
		// 		if(optical_sensor.get_hue() < 50){
		// 			intake.brake();
		// 			rollerToggle = !rollerToggle;
		// 		}
		// 	}
		// }
	
		
		
		/*else if(controller.get_digital_new_press(DIGITAL_LEFT)){
			testFlywheelSpeed = -600;
		}*/

		if(controller.get_digital_new_press(DIGITAL_Y)){
			changeFlywheelTarget(FLYWHEEL_SPEED_TARGET);
		}
		else if(controller.get_digital_new_press(DIGITAL_B)){
			changeFlywheelTarget(SINGLE_SPEED_TARGET);
		}
	
		
		if (controller.get_digital_new_press(DIGITAL_DOWN)){ //Spin up
			flywheelAllowed = !flywheelAllowed;
		}
		
		//REME BER
		if(flywheelAllowed == false) flywheelBrake(); //if(flywheelAllowed == false || indexToggle == false)
		else if(indexToggle) flywheelPDF();

		/*if(controller.get_digital_new_press(DIGITAL_X)){
			intakePiston.flip();
		}*/

		/*if(lineFollower.get_value() < 600 && lineFollower.get_value() > 0){
			detectedTime++;
		}
		else{
			detectedTime = 0;
		}

		if(detectedTime > 40){
			indexToggle = true;
		}*/
		indexToggle = true;

		// if(controller.get_digital_new_press(DIGITAL_R2)){
		// 	indexer.move_relative(ONE_DISK_ROTATION,400);
			
		// }
		//controller.get_digital_new_press(DIGITAL_R1) || controller.get_digital_new_press(DIGITAL_R2)
		

		if(controller.get_digital_new_press(DIGITAL_UP)){
			manualIndex = !manualIndex;
		}

		if(manualIndex){
			if(controller.get_digital(DIGITAL_LEFT)){
				indexer.move(-60);
			}
			else if(controller.get_digital(DIGITAL_RIGHT)){
				indexer.move(60);
			}
			else{
				indexer.move(0);
			}
		}

		if(indexToggle && controller.get_digital_new_press(DIGITAL_R1)){
			pros::Task tripleShotCall(tripleShot);
		}
		else if(indexToggle && controller.get_digital_new_press(DIGITAL_R2)){
			pros::Task singleShotCall(singleShot);
		}
		else{
			if(controller.get_digital_new_press(DIGITAL_R1) || controller.get_digital_new_press(DIGITAL_R2)){
				indexToggle = true;
			}
		}

		//std::cout << "freeze" << freezeTwoDiskIn << std::endl;
		//std::cout << "two" << twoDiskIn << std::endl;

		// else if(controller.get_digital_new_press(DIGITAL_R1)){
		// 	indexer.move_relative(ONE_DISK_ROTATION*3, 360);
		// }
	
		/*else if(controller.get_digital(DIGITAL_R1)){
			indexer.move(127);
		}*/
		/*else{
			indexer.move(0);
		}*/


		if(controller.get_digital_new_press(DIGITAL_L1) && controller.get_digital_new_press(DIGITAL_L2)){
			endBack.open();
		}
		else if(controller.get_digital(DIGITAL_L1)){
			rollerToggle = false;
			intake.move(127);
		}
		else if(controller.get_digital(DIGITAL_L2)){
			rollerToggle = false;
			intake.move(-127);
		}
		else if(rollerToggle == false){
			intake.move(0);
		}

		//Driver Curves

	
		float lPwr, rPwr;
		float rYaxis, lYaxis;
		rYaxis = controller.get_analog(ANALOG_RIGHT_Y);
		lYaxis = controller.get_analog(ANALOG_LEFT_Y);
		
		rPwr = (abs(rYaxis) > 2) ? (sgn(rYaxis) * (1.2*pow(1.03566426, sgn(rYaxis)*rYaxis) - 1.2 + sgn(rYaxis)*0.2*rYaxis)) : 0;
		lPwr = (abs(lYaxis) > 2) ? (sgn(lYaxis) * (1.2*pow(1.03566426, sgn(lYaxis)*lYaxis) - 1.2 + sgn(lYaxis)*0.2*lYaxis)) : 0;
		
		chas_move(lPwr, rPwr);

		pros::delay(10);

		count++;
	}

	

	// if(controller.get_digital_new_press(DIGITAL_DOWN) && (selectedTeam == 1)){
		// 	optical_sensor.set_led_pwm(90);
		// 	intakeOpticalSensorRed = !intakeOpticalSensorRed;
		// }
		// if(intakeOpticalSensorRed == true){
		// 	intake.move(-127);
		// 	if(optical_sensor.get_hue() > 100){
		// 		intake.brake();
		// 		intakeOpticalSensorRed = !intakeOpticalSensorRed;
		// 	}
		// }
	
	// if(controller.get_digital_new_press(DIGITAL_B) && (selectedTeam == -1)){
		// 	optical_sensor.set_led_pwm(90);
		// 	intakeOpticalSensorBlue = !intakeOpticalSensorBlue;
		// }
		// if(intakeOpticalSensorBlue == true){
		// 	intake.move(-127);
		// 	controller.print(2,0,"YES!");
		// 	if(optical_sensor.get_hue() < 100){
		// 		intake.brake();
		// 		intakeOpticalSensorBlue = !intakeOpticalSensorBlue;
		// 	}
		// }

		/*pros::lcd::print(3, "%f", leftE.get_value());
		pros::lcd::print(4, "%f", midE.get_value());
		pros::lcd::print(5, "%f", rightE.get_value());*/
		//std::cout << leftE.get_value() << std::endl;

		// //Flywheel Toggle
		// if (!(count % 25)){ //Printing average RPMS on to the screen
		// 
		// }
		// count ++;
		// pros::delay(2);
}