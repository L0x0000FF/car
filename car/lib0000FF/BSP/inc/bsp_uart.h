#ifndef BSP_UART_H
#define BSP_UART_H

#include "main.h"

class BSP_UART {
 private:
  UART_HandleTypeDef* phuart;
  void (*rxCallback)(void);

 public:
  BSP_UART();
  void init(UART_HandleTypeDef* phuart, void (*rxCallback)(void));
  void regRxCallback(void (*rxCallback)(void));
  void transmit(uint8_t* data, uint16_t size);
  void transmit(uint8_t* data, uint16_t size, uint32_t timeout);
  void receive(uint8_t* data, uint16_t size);
  void receive(uint8_t* data, uint16_t size, uint32_t timeout);
  bool isReadyForTx();
  static void UART_rxCallback(UART_HandleTypeDef* phuart);
};

#endif
