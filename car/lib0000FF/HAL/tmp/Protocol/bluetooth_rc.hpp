#ifndef BLUETOOTH_RC_HPP
#define BLUETOOTH_RC_HPP

#include "HC08.hpp"

class BLE_RC {
 private:
  BLE_HC08* ble;
 public:
  int16_t ch0;
  int16_t ch1;
  int16_t ch2;
  int16_t ch3;
  int16_t ch4;
  int16_t ch5;
  BLE_RC(BLE_HC08* ble);
  void update();
};

#endif
