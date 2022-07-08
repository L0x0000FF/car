#include "FSi6.hpp"

#include "string.h"

FSi6 rc;

FSi6::FSi6() {
  memset(this->rawData, 0, FSI6_RX_SIZE);
  memset(&data, 0, sizeof(FSi6_Data));
  memset(&last_data, 0, sizeof(FSi6_Data));
}

void FSi6::init(BSP_UART* phuart) {
  this->phuart = phuart;
  phuart->regRxCallback(rxCallback);
  phuart->receive(this->rawData, FSI6_RX_SIZE);
}

void FSi6::rxCallback() {
  rc.solve();
  rc.phuart->receive(rc.rawData,FSI6_RX_SIZE);
}

void FSi6::solve() {
  uint8_t i = 0;
  uint16_t checksum = 0;
  if (rawData[i] == 0x20 && rawData[++i] == 0x40) {
    last_data = data;
    i++;
    data.ch0 = ((uint16_t)rawData[i]) | ((uint16_t)rawData[i + 1] << 8);
    data.ch1 = ((uint16_t)rawData[i + 2]) | ((uint16_t)rawData[i + 3] << 8);
    data.ch2 = ((uint16_t)rawData[i + 4]) | ((uint16_t)rawData[i + 5] << 8);
    data.ch3 = ((uint16_t)rawData[i + 6]) | ((uint16_t)rawData[i + 7] << 8);
    data.ch4 = ((uint16_t)rawData[i + 8]) | ((uint16_t)rawData[i + 9] << 8);
    data.ch5 = ((uint16_t)rawData[i + 10]) | ((uint16_t)rawData[i + 11] << 8);
    data.ch6 = ((uint16_t)rawData[i + 12]) | ((uint16_t)rawData[i + 13] << 8);
    data.ch7 = ((uint16_t)rawData[i + 14]) | ((uint16_t)rawData[i + 15] << 8);
    data.ch8 = ((uint16_t)rawData[i + 16]) | ((uint16_t)rawData[i + 17] << 8);
    data.ch9 = ((uint16_t)rawData[i + 18]) | ((uint16_t)rawData[i + 19] << 8);
    data.ch10 = ((uint16_t)rawData[i + 20]) | ((uint16_t)rawData[i + 21] << 8);
    data.ch11 = ((uint16_t)rawData[i + 22]) | ((uint16_t)rawData[i + 23] << 8);
    data.ch12 = ((uint16_t)rawData[i + 24]) | ((uint16_t)rawData[i + 25] << 8);
    data.ch13 = ((uint16_t)rawData[i + 26]) | ((uint16_t)rawData[i + 27] << 8);
  }
  for (uint8_t j = 0; j < 30; j++) checksum += rawData[j];
  checksum ^= 0xFFFF;  // complement
  if (checksum == ((uint16_t)rawData[30] | (((uint16_t)rawData[31]) << 8)))
    data.isCorrect = true;
  else
    data.isCorrect = false;
}
