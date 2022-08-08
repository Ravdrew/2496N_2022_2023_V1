#include "main.h"
#include "robot.h"
#include "movement.h"
#include "PID.h"
#include "flywheel.h"
#include <cmath>
#define OPTICAL_PORT 1


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
	// pros::lcd::initialize();
	// pros::lcd::set_text(1, "Hello PROS User!");

	// pros::lcd::register_btn1_cb(on_center_button);
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
int selectedAuto = 1;

bool switchPressed = false;
bool resetNeeded = false;

int timer = 0;
void competition_initialize() {
	/*controller.clear();
	while (true) {

		if(plus.get_value() && !switchPressed){
			switchPressed = true;
			resetNeeded = true;
			selectedAuto += 1;
		}
		else if(plus.get_value() == false){
			switchPressed = false;
		}

		if(selectedAuto > MAX_AUTOS){
			resetNeeded = true;
			selectedAuto = 1;
		}
		
		if (!(timer % 25)) {
			if(resetNeeded){
				resetNeeded = false;
				controller.clear();
			}
			if(selectedAuto == 1) controller.set_text(1, 0, "AWP"); //will be awp
			else if(selectedAuto == 2) controller.set_text(1, 0, "Plat Down");
			else if(selectedAuto == 3) controller.set_text(1, 0, "Line Side");
			else if(selectedAuto == 4) controller.set_text(1, 0, "Elims");
			else if(selectedAuto == 5) controller.set_text(1, 0, "Rush Mid");
			else if(selectedAuto == 6) controller.set_text(1, 0, "Prog Skills");
			else if(selectedAuto == 7) controller.set_text(1, 0, "No Auton");
		}
		timer++;
		pros::delay(2);
	}*/
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

// void teamSelect(){
// 	int autonState = 0;
// 	bool buttonUnpressed = true;
// 	if(Switch.isPressed() && buttonUnpressed){
// 		autonState++;
// 		if(autonState==5){
// 			autonState = 0;
// 			buttonUnpressed = false;
// 		}
// 	}
// 		if(!Switch.isPressed()){
// 			buttonUnpressed = true;

// 		}	
// 	pros::delay(5);
// }

void autonSelect(){
	/*if(plus.get_value() && !switchPressed){
		switchPressed = true;
		resetNeeded = true;
		selectedAuto += 1;
	}
	else if(plus.get_value() == false){
		switchPressed = false;
	}

	if(selectedAuto > MAX_AUTOS){
		resetNeeded = true;
		selectedAuto = 1;
	}
	
	if (!(timer % 5)) {
		if(resetNeeded){
			resetNeeded = false;
			controller.clear();
		}
		if(selectedAuto == 1) controller.set_text(1, 0, "AWP"); //will be awp
		else if(selectedAuto == 2) controller.set_text(1, 0, "Plat Down");
		else if(selectedAuto == 3) controller.set_text(1, 0, "Line Side");
		else if(selectedAuto == 4) controller.set_text(1, 0, "Elims");
		else if(selectedAuto == 5) controller.set_text(1, 0, "Rush Mid");
		else if(selectedAuto == 6) controller.set_text(1, 0, "Prog Skills");
		else if(selectedAuto == 7) controller.set_text(1, 0, "No Auton");
	}
	timer++;*/
}

void opcontrol() {
	controller.clear();
	leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	outFlywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	midFlywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	int count = 0;
	bool intake_power = false;
	int intake_direction = 1;

	pros::Optical optical_sensor(1);
	pros::c::optical_rgb_s_t rgb_value;

	while (true) {

		
		// //Flywheel Toggle
		// if (!(count % 25)){ //Printing average RPMS on to the screen
		// 	controller.print(0,0,"%f %f", midFlywheel.get_actual_velocity(), outFlywheel.get_actual_velocity());
		// }
			count++;
			pros::delay(2);
		if (controller.get_digital(DIGITAL_L1)){ //Spin up
			outFlywheel.move(127);
			midFlywheel.move(127);
			
		}
		else if (controller.get_digital(DIGITAL_L2)) { //Spin down
			outFlywheel.brake();
			midFlywheel.brake();
		}
		
		// //Full intake code
		// if(!(count % 25)){
		// 	controller.print(2,0, "Intake: %f ", intake.get_actual_velocity());
		// }

		if(controller.get_digital_new_press(DIGITAL_R1)){
			intake_power = !intake_power;
		}

		if(controller.get_digital_new_press(DIGITAL_R2)){
			intake_direction = intake_direction * -1;
		}

		if(intake_power){
			intake.move(127*intake_direction); //Toggle Direction
		}
		else {
			intake.brake();
		}

		// //optical sensor
		// rgb_value = optical_sensor.get_rgb();
		// if(!(count % 25)){
		// controller.print(0,0,"Red: %lf \n", rgb_value.red);
		// }
		// count++;
		// pros::delay(2);

		// if(!(count % 25)){
		// 	controller.print(2,0,"Blue: %lf \n", rgb_value.blue);
		// }
		// count++;
		// pros::delay(2);
		
		// if(!(count % 25)){
		// controller.print(1,0,"Green: %lf \n", rgb_value.green);
		// }
		// count++;
		// pros::delay(2);
		

		//Driver Curves

		float lPwr, rPwr;
		float rYaxis, lYaxis;
		rYaxis = controller.get_analog(ANALOG_RIGHT_Y);
		lYaxis = controller.get_analog(ANALOG_LEFT_Y);
		
		rPwr = (abs(rYaxis) > 2) ? (sgn(rYaxis) * (1.2*pow(1.03566426, sgn(rYaxis)*rYaxis) - 1.2 + sgn(rYaxis)*0.2*rYaxis)) : 0;
		lPwr = (abs(lYaxis) > 2) ? (sgn(lYaxis) * (1.2*pow(1.03566426, sgn(lYaxis)*lYaxis) - 1.2 + sgn(lYaxis)*0.2*lYaxis)) : 0;
		
		chas_move(lPwr, rPwr);
	

		pros::delay(20);
	}

	/*
	int = 0;
	while(true){
		
		if controller.get_digital(DIGITAL_L1){
			if int = 0{
				int  = 1;
				vex::task::sleep(100)
			}
			else if int = 1{
				int = 0;
			}
		}
		if int = 1{
			
		}
	}*/

/*
	int hue_value = optical_sensor.get_hue();
	if (controller.get_digital(DIGITAL_L1)){
		if (hue_value <= 30 || hue_value >= 330){
			intake.move(127);
		} 
		else{
			intake.move(0);
		}
	} */

		/*
		//Optical Sensor Stuff
		int hue_value = optical_sensor.get_hue(); 
		if (hue_value <= 30 || hue_value >= 330){  
			intake.move(127);
		}
		else{
			intake.move(0);
		}
		*/
}