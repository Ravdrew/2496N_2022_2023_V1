#ifndef PID_A_H
#define PID_A_H

class PID{
public:
    float m_kp;
    float m_ki;
    float m_kd;
    float error = 0;
    float prev_error = 0;
    float integral = 0;
    float derivative = 0;
    float power = 0;
    float prev_power = 0;

    PID(float kp, float ki, float kd){ 
        m_kp = kp;
        m_ki = ki;
        m_kd = kd;
    }

    void changeConsts(float kp, float ki, float kd){
        m_kp = kp;
        m_ki = ki;
        m_kd = kd;
    }

    float calc (float target, float input, float integralKI, float maxI, float slew, bool slewq){ 
        prev_power = power;
        prev_error = error;
        error = target - input;

        std::abs(error) < integralKI? integral += error : integral = 0;
        integral >= 0? integral = std::min(integral, maxI) : integral = std::max(integral, -maxI);

        derivative = error - prev_error;

        power = m_kp*error + m_ki*integral + m_kd*derivative;

        if (slewq){
            if (power <= prev_power + slew){
                slewq = false;
            }
            else if (power - prev_power > slew){
                power = prev_power + slew;
            }
        }

        return power;
    }
};

#endif