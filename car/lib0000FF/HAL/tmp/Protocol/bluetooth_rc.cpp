#include "bluetooth_rc.hpp"

BLE_RC::BLE_RC(BLE_HC08* ble) { this->ble = ble; }

void BLE_RC::update() {
  uint16_t index = 0;
  while (ble->rxBuffer[index] != 0xA5 && index < ble->bufferLength - 2) {
    index++;
  }
  if (index == ble->bufferLength) return;
  ch0 = (int16_t)(ble->rxBuffer[index + 1] << 8) |
        (int16_t)ble->rxBuffer[index + 2];
  ch1 = (int16_t)(ble->rxBuffer[index + 3] << 8) |
        (int16_t)ble->rxBuffer[index + 4];
  ch2 = (int16_t)(ble->rxBuffer[index + 5] << 8) |
        (int16_t)ble->rxBuffer[index + 6];
  ch3 = (int16_t)(ble->rxBuffer[index + 7] << 8) |
        (int16_t)ble->rxBuffer[index + 8];
  ch4 = (int16_t)(ble->rxBuffer[index + 9] << 8) |
        (int16_t)ble->rxBuffer[index + 10];
}
