#include "bsp_uart.h"

#include <vector>

std::vector<BSP_UART*> uart_list;

BSP_UART::BSP_UART() {}

void BSP_UART::init(UART_HandleTypeDef* phuart, void (*rxCallback)(void)) {
  this->phuart = phuart;
  this->rxCallback = rxCallback;
  uart_list.push_back(this);
  __HAL_UART_ENABLE_IT(phuart, UART_IT_IDLE);
  HAL_DMA_DeInit(phuart->hdmarx);
  HAL_DMA_Init(phuart->hdmarx);
  HAL_DMA_DeInit(phuart->hdmatx);
  HAL_DMA_Init(phuart->hdmatx);
}

void BSP_UART::regRxCallback(void (*rxCallback)(void)) {
  this->rxCallback = rxCallback;
}

void BSP_UART::transmit(uint8_t* data, uint16_t size) {
  HAL_UART_Transmit_DMA(phuart, data, size);
}

void BSP_UART::transmit(uint8_t* data, uint16_t size, uint32_t timeout) {
  HAL_UART_Transmit(phuart, data, size, timeout);
}

void BSP_UART::receive(uint8_t* data, uint16_t size) {
  HAL_UART_Receive_DMA(phuart, data, size);
}

void BSP_UART::receive(uint8_t* data, uint16_t size, uint32_t timeout) {
  HAL_UART_Receive(phuart, data, size, timeout);
}

bool BSP_UART::isReadyForTx(){
  if(phuart->gState == HAL_UART_STATE_READY)return true;
  else return false;
}

void BSP_UART::UART_rxCallback(UART_HandleTypeDef* phuart) {
  for (uint8_t i = 0; i < uart_list.size(); i++) {
    if (phuart == uart_list[i]->phuart) {
      uint32_t tmp_flag = 0;
      uint32_t temp;
      tmp_flag = __HAL_UART_GET_FLAG(phuart, UART_FLAG_IDLE);  //获取IDLE标志位
      if ((tmp_flag != RESET)) {            // idle标志被置位
        __HAL_UART_CLEAR_IDLEFLAG(phuart);  //清除标志位
        temp =
            phuart->Instance
                ->SR;  //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能
        temp = phuart->Instance->DR;  //读取数据寄存器中的数据
        HAL_UART_DMAStop(phuart);     //
        temp = phuart->hdmarx->Instance->NDTR;  // 获取DMA中未传输的数据个数
        if (uart_list[i]->rxCallback != NULL) uart_list[i]->rxCallback();
      }
      break;
    }
  }
}
