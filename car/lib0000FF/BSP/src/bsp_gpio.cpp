#include "bsp_gpio.h"

#include <vector>

std::vector<GPIO*> gpio_list;

GPIO::GPIO() {
  this->EXTICallback = NULL;
}

void GPIO::init(GPIO_TypeDef* pGPIO, uint16_t pin) {
  this->pGPIO = pGPIO;
  this->pin = pin;
  gpio_list.push_back(this);
}

void GPIO::high() { HAL_GPIO_WritePin(pGPIO, pin, GPIO_PIN_SET); }

void GPIO::low() { HAL_GPIO_WritePin(pGPIO, pin, GPIO_PIN_RESET); }

void GPIO::toggle() { HAL_GPIO_TogglePin(pGPIO, pin); }

void GPIO::write(GPIO_PinState state) { HAL_GPIO_WritePin(pGPIO, pin, state); }

void GPIO::regEXTICallback(void (*EXTICallback)(uint16_t EXTI_line)) {
  this->EXTICallback = EXTICallback;
}

GPIO_PinState GPIO::read() { return HAL_GPIO_ReadPin(pGPIO, pin); }

void GPIO::GPIO_EXTICallback(uint16_t index) {
  for (uint8_t i = 0; i < gpio_list.size(); i++) {
    if (gpio_list[i]->pin == index && gpio_list[i]->EXTICallback != NULL) {
      gpio_list[i]->EXTICallback(index);
      break;
    }
  }
}

//BSP PWM:TODO
PWM::PWM(TIM_HandleTypeDef* htim, uint16_t channel) {
  this->htim = htim;
  this->channel = channel;
}

void PWM::setDutyRatio(float duty_ratio) {}

void PWM::setFreq(float Hz) {}

void PWM::start() {}

void PWM::stop() {}
