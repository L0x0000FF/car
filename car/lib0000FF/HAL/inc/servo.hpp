#ifndef SERVO_HPP
#define SERVO_HPP

#include "main.h"

#define SERVO_MIN_DUTY_RATE 0.025f
#define SERVO_MAX_DUTY_RATE 0.125f

class Servo {
 private:
  TIM_HandleTypeDef* phtim_power;
  uint32_t power_channel;
  float angle;

 public:
  Servo();
  void init(TIM_HandleTypeDef* phtim_power, uint32_t power_channel,float init_angle = 0.0f);
  void setCCR(uint16_t CCR);
  void setDutyRate(float duty_rate);
  void setAngle(float angle);

};

#endif
