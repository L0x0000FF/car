#include "usTimer.h"

#include "main.h"

UsTimer::UsTimer() { this->round = 0; }

void UsTimer::init(TIM_HandleTypeDef *phtim) {
  this->phtim = phtim;
  HAL_TIM_Base_Start_IT(phtim);
}

void UsTimer::update() { this->round++; }

uint32_t UsTimer::getTime() {
  return this->round * (this->phtim->Instance->ARR + 1) +
         (uint32_t)(this->phtim->Instance->CNT) + 1;
}

void UsTimer::delayms(uint32_t ms) {
  uint32_t time = this->getTime();
  while (this->getTime()< time+ms * 1000)
    ;
}

void UsTimer::delayus(uint32_t us) {
  uint32_t time = this->getTime();
  while (this->getTime()< time+us)
    ;
}
