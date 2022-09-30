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
//Gerald was here wassup guys another year on this team lmao//
#define TURN_INTEGRAL_KICK_IN 9
#define TURN_MAX_INTEGRAL 127

#define COUNT_CONST 25 //23

float start_heading;

void chas_move(int left_power, int right_power){
	leftFront.move(left_power);
	leftBack.move(left_power);
	rightFront.move(right_power);
	rightBack.move(right_power);
}

void quickie(float target){
    PID quickPID(QUICK_KP, QUICK_KI, QUICK_KD);
//wazzzzzzzaaaappppp how is it going lads
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
    
        if (abs(target - encoder_average) <= 5) count++;
        if (count >= 5) break;

        pros::delay(10);
    }
    
    chas_move(0,0);
}
//beep boop beep boop
void moveTimed(float target, int timer_amt){
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
//somos en el nave con el impostor 
void move(float target, bool ask_slew, float slew_rate, float power_cap, float active_cap){
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
//*skull emoji
void turn(float target, bool ask_slew, float slew_rate){
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

//void dn{}
void absturn(float abstarget, bool ask_slew, float slew_rate, float power_cap){
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

//who asked lol
void absturnTimed(float abstarget, float timer_amt, bool ask_slew, float slew_rate, float power_cap){
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
       if(abs(abstarget - position) <= 1.5) count++;
       if(count >= 30 || timer >= timer_amt) break;
 
       pros::delay(10);
   }
   chas_move(0,0);
   printf("count: %d\r\n", (count));
}

void moveOutakeTill(int speed, bool red){


}

