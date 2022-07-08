#ifndef LED_HPP
#define LED_HPP

#include "bsp_gpio.h"
#include "usTimer.h"

class LED{
 private:
  GPIO* gpio;
  uint8_t on_state;
  UsTimer* timer;
  float freq;
  bool isOn;
  uint8_t flash_times;
  uint8_t flash_cnt;
  uint8_t flash_state;  //0 for off,1 for flash_on,2 for flash_off
  uint32_t last_update_time;
 public:
  LED(GPIO* gpio, uint8_t on_state, UsTimer* timer, float freq = 50.0f);
  void on();
  void off();
  void flash(uint8_t times);
  void update();
};

#endif
