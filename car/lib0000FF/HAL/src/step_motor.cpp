#include "step_motor.hpp"

Step_Motor::Step_Motor() {
  this->phtim_pulse = NULL;
  this->ena = NULL;
  this->dir = NULL;
}

void Step_Motor::init(TIM_HandleTypeDef* phtim_pulse, uint32_t pulse_channel,
                      GPIO* ena, GPIO* dir) {
  this->phtim_pulse = phtim_pulse;
  this->pulse_channel = pulse_channel;
  this->ena = ena;
  this->dir = dir;
  this->setSpeed(0);
  HAL_TIM_PWM_Start(phtim_pulse, pulse_channel);
}

void Step_Motor::setSpeed(int32_t speed) {
  if (speed == 0)
    this->disable();
  else if (speed > 0) {
    this->dir->high();
    this->phtim_pulse->Instance->ARR = 1000000 / speed;
    __HAL_TIM_SET_COMPARE(this->phtim_pulse, this->pulse_channel,
                          this->phtim_pulse->Instance->ARR / 2);
    this->enable();
  } else if (speed < 0) {
    this->dir->low();
    this->phtim_pulse->Instance->ARR = 1000000 / -speed;
    __HAL_TIM_SET_COMPARE(this->phtim_pulse, this->pulse_channel,
                          this->phtim_pulse->Instance->ARR / 2);
    this->enable();
  }
}

void Step_Motor::enable() { this->ena->low(); }

void Step_Motor::disable() { this->ena->high(); }
