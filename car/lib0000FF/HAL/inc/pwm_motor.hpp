#ifndef PWM_MOTOR_HPP
#define PWM_MOTOR_HPP

#include "bsp_gpio.h"
#include "main.h"
#include "stdint.h"
#include "usTimer.h"

class PWM_Motor {
 private:
  TIM_HandleTypeDef* phtim_power;
  uint32_t power_channel;
  GPIO* encoder_A;
  GPIO* encoder_B;
  GPIO* in1;
  GPIO* in2;
  uint8_t id;

  UsTimer* ptimer;
  int output;
  int round;
  int real_position;
  int last_real_position;
  int encoder_cnt;
  int last_encoder_cnt;
  uint32_t last_update_time;
  float dt;

 public:
  float speed;
  PWM_Motor();
  void init(uint8_t id,TIM_HandleTypeDef* phtim_power, uint32_t power_channel,
            UsTimer* ptimer, GPIO* in1, GPIO* in2, GPIO* encoder_A,
            GPIO* encoder_B);
  void setOutput(int output);
  void update();
  static void PWM_Motor_encoder_update(uint16_t EXTI_line);
  void updateEncoder();
};

#endif
