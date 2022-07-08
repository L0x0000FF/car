#ifndef HC08_HPP
#define HC08_HPP

#include "main.h"

class BLE_HC08{
 private:
  UART_HandleTypeDef* phuart;

 public:
  uint8_t* rxBuffer;
  uint16_t bufferLength;
  BLE_HC08(uint16_t defaultBufferLength = 25);
  ~BLE_HC08();
  void init(UART_HandleTypeDef* phuart);
  void transmit(uint8_t* data, uint16_t size);
  void rxCallback();
};

#endif
