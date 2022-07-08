#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "pid.h"

template <class T>
class Motor_Control {
 private:
  float fdb_position;
  float fdb_speed;
  float ref_position;
  float ref_speed;
 public:
  Motor_Control(){
    
  }
};


#endif
