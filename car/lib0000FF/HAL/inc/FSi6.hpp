#ifndef FS_I6_HPP
#define FS_I6_HPP

#include "main.h"
#include "bsp_uart.h"

#define FSI6_RX_SIZE 32
#define IBUS_CH_MAX 2000
#define IBUS_CH_MIN 1000
#define IBUS_CH_BIAS 1500

typedef struct FSi6_Data {
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
  bool isCorrect;
} FSi6_Data;

class FSi6 {
 private:
  BSP_UART* phuart;
 public:
  uint8_t rawData[FSI6_RX_SIZE];
  FSi6_Data data;
  FSi6_Data last_data;

  FSi6();
  void init(BSP_UART* phuart);
  void solve();
  static void rxCallback();
};

extern FSi6 rc;

#endif
