#ifndef PISTON_A_H
#define PISTON_A_H

class Piston{
private:
    bool m_state;
    pros::ADIDigitalOut pp;

public:

    Piston(int port) : m_state(true), pp(port){}

    void open(){
        m_state = true;
        pp.set_value(true);
    }

    void close(){
        m_state = false;
        pp.set_value(false);
    }

    void flip(){
        if(m_state == false){
            open();
        }
        else if(m_state == true){
            close();
        }
    }

    bool getState(){
        return m_state;
    }
};

#endif