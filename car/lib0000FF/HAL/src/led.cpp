#include "led.hpp"

LED::LED(GPIO* gpio, uint8_t on_state, UsTimer* timer, float freq) {
  this->gpio = gpio;
  this->isOn = false;
  this->on_state = on_state;
  this->freq = freq;
  this->timer = timer;
  this->flash_times = 1;
  this->last_update_time = 0;
  this->flash_state = 0;
  this->flash_cnt = 0;
}

void LED::on() { this->isOn = true; }

void LED::off() { this->isOn = false; }

void LED::flash(uint8_t times) {
  this->flash_times = times;
  this->flash_state = 0;
}

void LED::update() {
  if (isOn) {
    if (flash_state == 0) {
      if (timer->getTime() - last_update_time >
          (uint32_t)(1 / freq * 1000000.0f)) {
        flash_state = 1;
        last_update_time = timer->getTime();
      } else
        gpio->write((GPIO_PinState)(~on_state));
    } else if (flash_state == 1) {
      if (timer->getTime() - last_update_time >
          (uint32_t)(1 / freq * 250000.0f)) {
        flash_state = 2;
        last_update_time = timer->getTime();
        flash_cnt++;
      } else
        gpio->write((GPIO_PinState)(on_state));
    } else if (flash_state == 2) {
      if (timer->getTime() - last_update_time >
          (uint32_t)(1 / freq * 250000.0f)) {
        if (flash_cnt >= flash_times) {
          flash_state = 0;
          flash_cnt = 0;
        } else
          flash_state = 1;
        last_update_time = timer->getTime();
      } else
        gpio->write((GPIO_PinState)(~on_state));
    }
  }
}
