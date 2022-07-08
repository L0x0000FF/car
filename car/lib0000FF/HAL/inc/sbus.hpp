#ifndef SBUS_HPP
#define SBUS_HPP

#include "bsp_uart.h"
#include "main.h"

#define SBUS_RX_SIZE 25
#define SBUS_CH_MAX 1792
#define SBUS_CH_MIN 192
#define SBUS_CH_BIAS 992

typedef struct SBUS_Data {
  uint16_t ch0;
  uint16_t ch1;
  uint16_t ch2;
  uint16_t ch3;
  uint16_t ch4;
  uint16_t ch5;
  uint16_t ch6;
  uint16_t ch7;
  uint16_t ch8;
  uint16_t ch9;
  uint16_t ch10;
  uint16_t ch11;
  uint16_t ch12;
  uint16_t ch13;
  uint16_t ch14;
  uint16_t ch15;
  uint16_t ch16;
  uint8_t flag;
} SBUS_Data;

class SBUS {
 private:
  BSP_UART* phuart;

 public:
  uint8_t rawData[SBUS_RX_SIZE];
  SBUS_Data data;
  SBUS_Data last_data;

  SBUS();
  void init(BSP_UART* phuart);
  void solve();
  static void rxCallback();
};

extern SBUS rc;

#endif
