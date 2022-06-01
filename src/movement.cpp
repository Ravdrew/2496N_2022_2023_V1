#include "main.h"
#include "PID.h"
#include "movement.h"
#include "robot.h"
#define STRAIGHT_KP 0.38 //0.39 0.5
#define STRAIGHT_KI 0.07 //0.15
#define STRAIGHT_KD 0.0
#define QUICK_KP 0.45 //0.39 0.5
#define QUICK_KI 0.05 //0.15
#define QUICK_KD 0.0
#define TURN_KP 2.3 //1.2
#define TURN_KI 0.15 //0.4
#define TURN_KD 0.0

#define STRAIGHT_INTEGRAL_KICK_IN 50
#define STRAIGHT_MAX_INTEGRAL 100

#define TURN_INTEGRAL_KICK_IN 9
#define TURN_MAX_INTEGRAL 127

#define COUNT_CONST 25 //23

//bool autonOn;

float start_heading;

void chas_move(int left_power, int right_power){
	leftFront.move(left_power);
	leftMid.move(left_power);
	leftBack.move(left_power);
	rightFront.move(right_power);
	rightMid.move(right_power);
	rightBack.move(right_power);
}

bool openStick;
bool openChain;
bool openJS;
bool openHood;

void chainClawOpen(){
	chainClaw.set_value(true);
    openChain = true;
}

void chainClawClose(){
	chainClaw.set_value(false);
    openChain = false;
}

void jsClawOpen(){
	jSClamp.set_value(true);
    openJS = true;
}

void jsClawClose(){
	jSClamp.set_value(false);
    openJS = false;
}

void stickUp(){
	stick.set_value(false);
    openStick = false;
}

void stickDown(){
	stick.set_value(true);
    openStick = true;
}

void hoodOpen(){
	hood.set_value(true);
    openHood = true;
}

void hoodClose(){
	hood.set_value(false);
    openHood = true;
}

void quickie(int target, bool claw){
    PID quickPID(QUICK_KP, QUICK_KI, QUICK_KD);

    float voltage;
    float encoder_average;

    float imu_offset;
    float heading;
    int count = 0;

    reset_encoders();
    imu_offset = imu.get_rotation();

    int printTimer = 0;
    float printPos = 0;
    controller.clear();

    while(true){
        printPos = target-encoder_average;
        if (!(printTimer % 5)) {
            //controller.clear();
            controller.print(0,0, "%f", printPos);
        }
        printTimer += 1;

        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        voltage = quickPID.calc(target, encoder_average, STRAIGHT_INTEGRAL_KICK_IN, STRAIGHT_INTEGRAL_KICK_IN, 0, false);

        //std::abs(voltage) > power_cap ? voltage = power_cap*voltage/std::abs(voltage) : voltage = voltage;
        chas_move(voltage, voltage); // (voltage - heading, voltage + heading)
        if (abs(target - encoder_average) <= 10) chainClawClose();
        if (abs(target - encoder_average) <= 5) count++;
        if (count >= 5) break;

        pros::delay(10);
    }
    
    chas_move(0,0);
}

void moveTimed(int target, int timer_amt){
   PID absMove(TURN_KP, TURN_KI, TURN_KD);
  
   float voltage;
   float encoder_average;
   int count = 0;
   int timer = 0;
    controller.clear();
    reset_encoders();

   while(true){
       encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
       voltage = absMove.calc(target, encoder_average, STRAIGHT_INTEGRAL_KICK_IN, STRAIGHT_MAX_INTEGRAL, 0, false);
       chas_move(voltage, voltage);
       if(abs(target - encoder_average) <= 50) timer++;
       if(timer > timer_amt) break;
       if (abs(target - encoder_average) <= 3) count++;
       if (count >= 23) break;
 
       pros::delay(10);
   }
   chas_move(0,0);
   printf("count: %d\r\n", (count));
}

void move(int target, bool ask_slew, int slew_rate, int power_cap, int active_cap){
    PID straight(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);

    float voltage;
    float encoder_average;

    float imu_offset;
    float heading;
    int count = 0;

    reset_encoders();
    imu_offset = imu.get_rotation();

    int printTimer = 0;
    float printPos = 0;
    controller.clear();
    
    while(true){

        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        voltage = straight.calc(target, encoder_average, STRAIGHT_INTEGRAL_KICK_IN, STRAIGHT_MAX_INTEGRAL, slew_rate, ask_slew);

        heading = 0;

        //std::abs(voltage) > power_cap ? voltage = power_cap*voltage/std::abs(voltage) : voltage = voltage;
        if(active_cap != 0){
            if(abs(target-encoder_average) <= active_cap){
                std::abs(voltage) > power_cap ? voltage = power_cap*voltage/std::abs(voltage) : voltage = voltage;
            }
        }
        else{
            std::abs(voltage) > power_cap ? voltage = power_cap*voltage/std::abs(voltage) : voltage = voltage;
        }

        chas_move(voltage - heading, voltage + heading); // (voltage - heading, voltage + heading)
        if (abs(target - encoder_average) <= 3) count++;
        if (count >= 23) break;

        pros::delay(10);
    }
    
    chas_move(0,0);
}

void goalYoink(){
    PID straight(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);

    float voltage;
    float encoder_average;

    float heading;
    float imu_offset;
    int count = 0;

    reset_encoders();
    imu_offset = imu.get_rotation();
    
    int target = 360;
    stickDown();
    while(true){

        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        voltage = straight.calc(target, encoder_average, STRAIGHT_INTEGRAL_KICK_IN, STRAIGHT_MAX_INTEGRAL, 0, false);

        if(abs(target - encoder_average) >= 120){
            voltage = 127;
        }
        //std::abs(voltage) > power_cap ? voltage = power_cap*voltage/std::abs(voltage) : voltage = voltage;
        heading = 0;

        chas_move(voltage, voltage + heading); // (voltage - heading, voltage + heading)
        if (abs(target - encoder_average) <= 80){
            stickUp();
        }
        if (abs(target - encoder_average) <= 3) break;

        pros::delay(10);
    }

    target = -500;
    reset_encoders();
    while(true){

        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        voltage = straight.calc(target, encoder_average, STRAIGHT_INTEGRAL_KICK_IN, STRAIGHT_MAX_INTEGRAL, 0, false);

        if(abs(target - encoder_average) >= 300){
            voltage = -127;
        }

        chas_move(voltage, voltage); // (voltage - heading, voltage + heading)
        if(abs(target - encoder_average) <= 243) stickDown();
        if(abs(target - encoder_average) <= 5) count++;
        if (count >= 23){
            break;
        }

        pros::delay(10);
    }    
    
    chas_move(0,0);
    stickUp();
}

void goalYoinkLeft(){
    PID straight(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);

    float voltage;
    float encoder_average;

    float heading;
    float imu_offset;
    int count = 0;

    reset_encoders();
    imu_offset = imu.get_rotation();
    
    int target = 350;
    stickDown();
    while(true){

        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        voltage = straight.calc(target, encoder_average, STRAIGHT_INTEGRAL_KICK_IN, STRAIGHT_MAX_INTEGRAL, 0, false);

        if(abs(target - encoder_average) >= 120){
            voltage = 127;
        }
        //std::abs(voltage) > power_cap ? voltage = power_cap*voltage/std::abs(voltage) : voltage = voltage;
        heading = 0;

        chas_move(voltage, voltage + heading); // (voltage - heading, voltage + heading)
        if (abs(target - encoder_average) <= 80){
            stickUp();
        }
        if (abs(target - encoder_average) <= 3) break;

        pros::delay(10);
    }

    target = -390;
    reset_encoders();
    while(true){

        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        voltage = straight.calc(target, encoder_average, STRAIGHT_INTEGRAL_KICK_IN, STRAIGHT_MAX_INTEGRAL, 0, false);

        if(abs(target - encoder_average) >= 145){
            voltage = -127;
        }

        chas_move(voltage, voltage); // (voltage - heading, voltage + heading)
        if(abs(target - encoder_average) <= 278) stickDown();
        if(abs(target - encoder_average) <= 5) count++;
        if (count >= 23){
            break;
        }

        pros::delay(10);
    }    
    
    chas_move(0,0);
    stickUp();
}

void goalYoinkMid(){
    PID straight(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);

    float voltage;
    float encoder_average;

    float heading;
    float imu_offset;
    int count = 0;

    reset_encoders();
    imu_offset = imu.get_rotation();
    
    int target = 390;
    stickDown();
    while(true){

        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        voltage = straight.calc(target, encoder_average, STRAIGHT_INTEGRAL_KICK_IN, STRAIGHT_MAX_INTEGRAL, 0, false);

        if(abs(target - encoder_average) >= 120){
            voltage = 127;
        }
        //std::abs(voltage) > power_cap ? voltage = power_cap*voltage/std::abs(voltage) : voltage = voltage;
        heading = 0;

        chas_move(voltage, voltage + heading); // (voltage - heading, voltage + heading)
        if (abs(target - encoder_average) <= 80){
            stickUp();
        }
        if (abs(target - encoder_average) <= 3) break;

        pros::delay(10);
    }

    target = -390;
    reset_encoders();
    while(true){

        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        voltage = straight.calc(target, encoder_average, STRAIGHT_INTEGRAL_KICK_IN, STRAIGHT_MAX_INTEGRAL, 0, false);

        if(abs(target - encoder_average) >= 145){
            voltage = -127;
        }

        chas_move(voltage, voltage); // (voltage - heading, voltage + heading)
        if(abs(target - encoder_average) <= 278) stickDown();
        if(abs(target - encoder_average) <= 5) count++;
        if (count >= 23){
            break;
        }

        pros::delay(10);
    }    
    
    chas_move(0,0);
    stickUp();
}

/*void goalYoink(int far){
    stickDown();
    PID yoink(1.2, 0.15, STRAIGHT_KD);

    float voltage;
    float encoder_average;

    float imu_offset;
    float heading;
    float target;
    bool stick_down = false;
    reset_encoders();
    imu_offset = imu.get_rotation();
    
    target = far;
    while(true){ 
        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        /*(if(abs(target - encoder_average) >= 150){
            voltage = 127;
        }
        if(abs(target - encoder_average) >= 100){
            voltage = 80;
        }
        else{
            voltage = 60;
        }*/
        /*voltage = yoink.calc(target, encoder_average, INTEGRAL_KICK_IN, MAX_INTEGRAL, 0, false);

        heading = imu.get_rotation() - imu_offset;

        chas_move(voltage - heading, voltage + heading); // (voltage - heading, voltage + heading)
        if (abs(target - encoder_average) <= 3) stickUp();
        if (abs(target - encoder_average) <= 3) break;

        pros::delay(10);
    }

    reset_encoders();
    while(true){ 
        encoder_average = (leftBack.get_position() + rightBack.get_position())/2;
        
        voltage = yoink.calc(-120, encoder_average, INTEGRAL_KICK_IN, MAX_INTEGRAL, 0, false);
        if (abs(-120 - encoder_average) <= 90){
            voltage = -127;
        }
        

        heading = imu.get_rotation() - imu_offset;

        chas_move(voltage + heading, voltage - heading); // (voltage + heading, voltage - heading\)
        if (abs(-120 - encoder_average) <= 60) stickDown();
        if (abs(-120 - encoder_average) <= 3) break;

        pros::delay(10);
    }
    chas_move(0,0);
}*/

void turn(float target, bool ask_slew, int slew_rate){
    PID rotate(TURN_KP, TURN_KI, TURN_KD);

    float voltage;
    float position;
    int count = 0;
    float imu_start;

    imu_start = imu.get_rotation();

    while(true){
        position = imu.get_rotation() - imu_start;
        voltage = rotate.calc(target, position, TURN_INTEGRAL_KICK_IN, TURN_MAX_INTEGRAL, slew_rate, ask_slew);

        chas_move(voltage, -voltage);
        printf("error: %f\r\n", (imu.get_rotation()));
        if (abs(target - position) <= 2) count++;
        if (count >= COUNT_CONST) break;

        pros::delay(10);
    }

    chas_move(0,0);
    printf("count: %d\r\n", (count));
}
void absturn(int abstarget, bool ask_slew, int slew_rate, int power_cap){
    PID absRotate(TURN_KP, TURN_KI, TURN_KD);
  
    float voltage;
    float position;
    int count = 0;
 
    int printTimer = 0;
    float printPos = 0;
    controller.clear();
    
    while(true){
        printPos = imu.get_rotation() - start_heading;
        if (!(printTimer % 5)) {
            //controller.clear();
            controller.print(0,0, "%f", printPos);
        }
        printTimer += 1;

        position = std::fmod(imu.get_rotation() - start_heading, 360);
        voltage = absRotate.calc(abstarget, position, TURN_INTEGRAL_KICK_IN, TURN_MAX_INTEGRAL, slew_rate, ask_slew);
        std::abs(voltage) > power_cap ? voltage = power_cap*voltage/std::abs(voltage) : voltage = voltage;
        chas_move(voltage, -voltage);

        if (abs(abstarget - position) <= 1) count++;
        if (count >= 100) break;

        pros::delay(10);
    }
    chas_move(0,0);
    printf("count: %d\r\n", (count));
}

void absturnTimed(int abstarget, int timer_amt, bool ask_slew, int slew_rate, int power_cap){
   PID absRotateTimed(TURN_KP, TURN_KI, TURN_KD);
  
   float voltage;
   float position;
   int count = 0;
   int timer = 0;
    
    int printTimer = 0;
    float printPos = 0;
    controller.clear();
   while(true){
       printPos = imu.get_rotation() - start_heading;
        if (!(printTimer % 25)) {
            //controller.clear();
            controller.print(0,0, "%f", printPos);
        }
       position = std::fmod(imu.get_rotation() - start_heading, 360);
       voltage = absRotateTimed.calc(abstarget, position, TURN_INTEGRAL_KICK_IN, TURN_MAX_INTEGRAL, slew_rate, ask_slew);
       std::abs(voltage) > power_cap ? voltage = power_cap*voltage/std::abs(voltage) : voltage = voltage;
       chas_move(voltage, -voltage);
       printf("error: %f\r\n", (imu.get_rotation()));
       if(abs(abstarget - position) <= 230) timer++;
       if (abs(abstarget - position) <= 1.5) count++;
       if (count >= 30 || timer >= timer_amt) break;
 
       pros::delay(10);
   }
   chas_move(0,0);
   printf("count: %d\r\n", (count));
}

/*bool chainGoalDetected(){
    if(chainSense.get_value() < 2150) return true;
    return false;
}*/

void moveTillChain(int speed, int timer){
    chainClawOpen();
    int count = 0;
    chas_move(speed, speed);
    while(count < timer){
        ++count;
        pros::delay(10);
    }
    chainClawClose();
    chas_move(0,0);
}

void moveTillJS(int speed, int timer){
    jsClawOpen();
    int count = 0;
    chas_move(speed, speed);
    while(count < timer){
        ++count;
        pros::delay(10);
    }
    jsClawClose();
    chas_move(0,0);
}

