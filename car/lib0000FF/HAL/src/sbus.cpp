#include "sbus.hpp"

#include "string.h"

SBUS rc;

SBUS::SBUS() {
  memset(this->rawData, 0, SBUS_RX_SIZE);
  memset(&data, 0, sizeof(SBUS_Data));
  memset(&last_data, 0, sizeof(SBUS_Data));
}

void SBUS::init(BSP_UART* phuart) {
  this->phuart = phuart;
  phuart->regRxCallback(rxCallback);
  phuart->receive(this->rawData, SBUS_RX_SIZE);
}

void SBUS::rxCallback() {
  rc.solve();
  rc.phuart->receive(rc.rawData, SBUS_RX_SIZE);
}

void SBUS::solve() {
  uint8_t i = 0;
  if (rawData[0] == 0x0F && rawData[SBUS_RX_SIZE - 1] == 0x00) {
    last_data = data;
    i++;
    // data.ch0 =
    //     ((uint16_t)rawData[i]) | (((uint16_t)rawData[i + 1] << 8) & 0x07FF);
    // data.ch1 = (((uint16_t)rawData[i + 1]) >> 3) |
    //            (((uint16_t)rawData[i + 2] << 5) & 0x07FF);
    // data.ch2 = (((uint16_t)rawData[i + 2]) >> 6) |
    //            ((uint16_t)rawData[i + 3] << 2) |
    //            (((uint16_t)rawData[i + 4] << 10) & 0x07FF);
    // data.ch3 = (((uint16_t)rawData[i + 4]) >> 1) |
    //            (((uint16_t)rawData[i + 5] << 7) & 0x07FF);
    // data.ch4 = (((uint16_t)rawData[i + 5]) >> 4) |
    //            (((uint16_t)rawData[i + 6] << 4) & 0x07FF);
    // data.ch5 = (((uint16_t)rawData[i + 6]) >> 7) |
    //            ((uint16_t)rawData[i + 7] << 1) |
    //            (((uint16_t)rawData[8] << 9) & 0x07FF);
    // data.ch6 = ((uint16_t)rawData[i + 8] >> 2) |
    //            (((uint16_t)rawData[i + 9] << 6) & 0x07FF);
    // data.ch7 =
    //     ((uint16_t)rawData[i + 9] >> 5) | ((uint16_t)rawData[i + 10] << 8);
    // data.ch8 = ((uint16_t)rawData[i + 16]) | ((uint16_t)rawData[i + 17] <<
    // 8); data.ch9 = ((uint16_t)rawData[i + 18]) | ((uint16_t)rawData[i + 19]
    // << 8); data.ch10 = ((uint16_t)rawData[i + 20]) | ((uint16_t)rawData[i +
    // 21] << 8); data.ch11 = ((uint16_t)rawData[i + 22]) | ((uint16_t)rawData[i
    // + 23] << 8); data.ch12 = ((uint16_t)rawData[i + 24]) |
    // ((uint16_t)rawData[i + 25] << 8); data.ch13 = ((uint16_t)rawData[i + 26])
    // | ((uint16_t)rawData[i + 27] << 8);

    // data.ch1 = ((uint16_t)rawData[1]) | ((uint16_t)((rawData[2] & 0x07) <<
    // 8)); data.ch2 = ((uint16_t)((rawData[2] & 0xf8) >> 3)) |
    //            (((uint16_t)(rawData[3] & 0x3f)) << 6);
    // data.ch3 = ((uint16_t)((rawData[3] & 0xc0) >> 6)) |
    //            ((((uint16_t)rawData[4]) << 2)) |
    //            (((uint16_t)(rawData[5] & 0x01)) << 10);
    // data.ch4 = ((uint16_t)((rawData[5] & 0xfe) >> 1)) |
    //            (((uint16_t)(rawData[6] & 0x0f)) << 7);
    // data.ch5 = ((uint16_t)((rawData[6] & 0xf0) >> 4)) |
    //            (((uint16_t)(rawData[7] & 0x7f)) << 4);
    // data.ch6 = ((uint16_t)((rawData[7] & 0x80) >> 7)) |
    //            (((uint16_t)rawData[8]) << 1) |
    //            (((uint16_t)(rawData[9] & 0x03)) << 9);
    // data.ch7 = ((uint16_t)((rawData[9] & 0xfc) >> 2)) |
    //            (((uint16_t)(rawData[10] & 0x1f)) << 6);
    // data.ch8 = ((uint16_t)((rawData[10] & 0xe0) >> 5)) |
    //            (((uint16_t)(rawData[11])) << 3);
    // data.ch9 =
    //     ((uint16_t)rawData[12]) | (((uint16_t)(rawData[13] & 0x07)) << 8);
    // data.ch10 = ((uint16_t)((rawData[13] & 0xf8) >> 3)) |
    //             (((uint16_t)(rawData[14] & 0x3f)) << 5);
    // data.ch11 = ((uint16_t)((rawData[14] & 0xc0) >> 6)) |
    //             (((uint16_t)rawData[15]) << 2) |
    //             (((uint16_t)(rawData[16] & 0x01)) << 10);
    // data.ch12 = ((uint16_t)((rawData[16] & 0xfe) >> 1)) |
    //             (((uint16_t)(rawData[17] & 0x0f)) << 7);
    // data.ch13 = ((uint16_t)((rawData[17] & 0xf0) >> 4)) |
    //             (((uint16_t)(rawData[18] & 0x7f)) << 4);
    // data.ch14 = ((uint16_t)((rawData[18] & 0x80) >> 7)) |
    //             (((uint16_t)rawData[19]) << 1) |
    //             (((uint16_t)(rawData[20] & 0x03)) << 9);
    // data.ch15 = ((uint16_t)((rawData[20] & 0xfc) >> 2)) |
    //             (((uint16_t)(rawData[21] & 0x1f)) << 6);
    // data.ch16 = ((uint16_t)((rawData[21] & 0xe0) >> 5)) |
    //             (((uint16_t)rawData[22]) << 3);

    data.ch0 = (int16_t)rawData[1] | ((int16_t)rawData[2] << 8) & 0x07FF;
    data.ch1 = (int16_t)rawData[2] >> 3 | ((int16_t)rawData[3] << 5) & 0x07FF;
    data.ch2 = ((int16_t)rawData[3] >> 6 | ((int16_t)rawData[4] << 2) |
                (int16_t)rawData[5] << 10) &
               0x07FF;
    data.ch3 = ((int16_t)rawData[5] >> 1 | ((int16_t)rawData[6] << 7)) & 0x07FF;
    data.ch4 = ((int16_t)rawData[6] >> 4 | ((int16_t)rawData[7] << 4)) & 0x07FF;
    data.ch5 = ((int16_t)rawData[7] >> 7 | ((int16_t)rawData[8] << 1) |
                (int16_t)rawData[9] << 9) &
               0x07FF;
    data.ch6 =
        ((int16_t)rawData[9] >> 2 | ((int16_t)rawData[10] << 6)) & 0x07FF;
    data.ch7 =
        ((int16_t)rawData[10] >> 5 | ((int16_t)rawData[11] << 3)) & 0x07FF;

    data.ch8 =
        ((int16_t)rawData[12] << 0 | ((int16_t)rawData[13] << 8)) & 0x07FF;
    data.ch9 =
        ((int16_t)rawData[13] >> 3 | ((int16_t)rawData[14] << 5)) & 0x07FF;
    data.ch10 = ((int16_t)rawData[14] >> 6 | ((int16_t)rawData[15] << 2) |
                 (int16_t)rawData[16] << 10) &
                0x07FF;
    data.ch11 =
        ((int16_t)rawData[16] >> 1 | ((int16_t)rawData[17] << 7)) & 0x07FF;
    data.ch12 =
        ((int16_t)rawData[17] >> 4 | ((int16_t)rawData[18] << 4)) & 0x07FF;
    data.ch13 = ((int16_t)rawData[18] >> 7 | ((int16_t)rawData[19] << 1) |
                 (int16_t)rawData[20] << 9) &
                0x07FF;
    data.ch14 =
        ((int16_t)rawData[20] >> 2 | ((int16_t)rawData[21] << 6)) & 0x07FF;
    data.ch15 =
        ((int16_t)rawData[21] >> 5 | ((int16_t)rawData[22] << 3)) & 0x07FF;
    data.flag = rawData[23];
  }
}
