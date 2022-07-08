#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "main.h"

class GPIO {
 private:
 public:
  GPIO_TypeDef* pGPIO;
  uint16_t pin;
  void (*EXTICallback)(uint16_t EXTI_line);
  GPIO();
  void init(GPIO_TypeDef* pGPIO, uint16_t pin);
  void high();
  void low();
  void toggle();
  void write(GPIO_PinState state);
  void regEXTICallback(void (*EXTICallback)(uint16_t EXTI_line));
  GPIO_PinState read();
  static void GPIO_EXTICallback(uint16_t index);
};

// BSP PWM:TODO
class PWM {
 private:
  TIM_HandleTypeDef* htim;
  uint16_t channel;

 public:
  PWM(TIM_HandleTypeDef* htim, uint16_t channel);
  void setDutyRatio(float duty_ratio);
  void setFreq(float Hz);
  void start();
  void stop();
};

#endif  // BSP_GPIO_H
