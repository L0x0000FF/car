#include "servo.hpp"

#define ANGLE_2_DUTYRATE (SERVO_MAX_DUTY_RATE - SERVO_MIN_DUTY_RATE) / 360.0f

Servo::Servo() {
  this->phtim_power = NULL;
}

void Servo::init(TIM_HandleTypeDef* phtim_power, uint32_t power_channel,
                 float init_angle) {
  this->phtim_power = phtim_power;
  this->power_channel = power_channel;
  setAngle(init_angle);
  HAL_TIM_PWM_Start(phtim_power,power_channel);
}

void Servo::setCCR(uint16_t CCR) {
  if (CCR > SERVO_MAX_DUTY_RATE * phtim_power->Instance->ARR)
    CCR = SERVO_MAX_DUTY_RATE * phtim_power->Instance->ARR;
  if (CCR < SERVO_MIN_DUTY_RATE * phtim_power->Instance->ARR)
    CCR = SERVO_MIN_DUTY_RATE * phtim_power->Instance->ARR;
  __HAL_TIM_SET_COMPARE(phtim_power, power_channel, CCR);
}
void Servo::setDutyRate(float duty_rate) {
  setCCR((uint16_t)(duty_rate * phtim_power->Instance->ARR));
}

void Servo::setAngle(float angle) {
  this->angle = angle;
  setDutyRate(angle * ANGLE_2_DUTYRATE + SERVO_MIN_DUTY_RATE);
}
