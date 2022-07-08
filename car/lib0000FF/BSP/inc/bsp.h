#ifndef APP_H
#define APP_H

// Includes
#include <stdint.h>

#include "main.h"

// C functions
#ifdef __cplusplus
extern "C" {
#endif

void BSP_init(void);
void BSP_defaultTask(void);

// Callbacks
void EXTICallback(uint16_t index);
void uartCallback(UART_HandleTypeDef* phuart);
void timCallback(TIM_HandleTypeDef* phtim);
void c_delay(uint16_t us);

#ifdef __cplusplus
}
#endif

extern uint8_t bsp_inited;

#endif
