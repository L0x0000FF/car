#ifndef US_TIMER_HPP
#define US_TIMER_HPP

#include <stdint.h>

#include "main.h"

class UsTimer {
 private:
  uint32_t round;

 public:
  TIM_HandleTypeDef *phtim;
  UsTimer();
  void init(TIM_HandleTypeDef *phtim);
  void update();
  uint32_t getTime();
  void delayms(uint32_t ms);
  void delayus(uint32_t us);
};

#endif  // US_TIMER_HPP
