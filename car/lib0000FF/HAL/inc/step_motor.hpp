#ifndef STEP_MOTOR_HPP
#define STEP_MOTOR_HPP

#include "bsp_gpio.h"
#include "main.h"

class Step_Motor {
 private:
  TIM_HandleTypeDef* phtim_pulse;
  uint32_t pulse_channel;
  GPIO* ena;  //使能控制，高电平有效
  GPIO* dir;  //正反转控制

 public:
  Step_Motor();
  void init(TIM_HandleTypeDef* phtim_pulse, uint32_t pulse_channel, GPIO* ena,
            GPIO* dir);
  void setSpeed(int32_t speed);  // pulse/s
  void enable();
  void disable();
};

#endif
