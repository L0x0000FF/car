#include "HC08.hpp"
#include "string.h"

BLE_HC08::BLE_HC08(uint16_t defaultBufferLength) {
  this->bufferLength = defaultBufferLength;
  this->rxBuffer = new uint8_t[defaultBufferLength];
  memset(rxBuffer, 0, defaultBufferLength);
}

BLE_HC08::~BLE_HC08() {
  delete this->rxBuffer;
}

void BLE_HC08::init(UART_HandleTypeDef* phuart) {
  this->phuart = phuart;
  __HAL_UART_ENABLE_IT(phuart,UART_IT_IDLE);
  HAL_UART_Receive_DMA(phuart,rxBuffer,25);
}

void BLE_HC08::transmit(uint8_t* data, uint16_t size) {
  HAL_UART_Transmit_DMA(phuart,data,size);
}

void BLE_HC08::rxCallback() {
  uint32_t tmp_flag = 0;
  uint32_t temp;
  tmp_flag = __HAL_UART_GET_FLAG(phuart, UART_FLAG_IDLE);  //获取IDLE标志位
  if ((tmp_flag != RESET)) {             // idle标志被置位
    __HAL_UART_CLEAR_IDLEFLAG(phuart);  //清除标志位
    temp = phuart->Instance
               ->SR;  //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能
    temp = phuart->Instance->DR;  //读取数据寄存器中的数据
    HAL_UART_DMAStop(phuart);   //
    temp = phuart->hdmarx->Instance->CNDTR;  // 获取DMA中未传输的数据个数
    HAL_UART_Receive_DMA(phuart,rxBuffer,bufferLength);
  }
}
