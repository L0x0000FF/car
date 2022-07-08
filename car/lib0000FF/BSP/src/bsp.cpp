#include "bsp.h"

#include "bsp_can.h"
#include "bsp_gpio.h"
#include "bsp_i2c.h"
#include "bsp_uart.h"
#include "usTimer.h"

// externs
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim14;

// Peripherals
UsTimer usTimer;
BSP_UART uart1;
BSP_UART uart3;
// EXTI PINS FOR ENCODER A
GPIO PA4;
GPIO PC3;
GPIO PF10;
GPIO PI0;
// NORMAL PINS FOR ENCODER B
GPIO PF0;
GPIO PE4;
GPIO PE5;
GPIO PE6;
// L298N IN1
GPIO PC0;
GPIO PC4;
GPIO PI2;
GPIO PI6;
// L298N IN2
GPIO PC1;
GPIO PC5;
GPIO PI5;
GPIO PI7;
// Step motor
GPIO PC2;  // DIR
GPIO PI9;  // ENA

uint8_t bsp_inited = 0;
uint32_t time = 0;

void BSP_init(void) {
  bsp_inited = 1;
  usTimer.init(&htim14);
  uart1.init(&huart1, NULL);
  uart3.init(&huart3, NULL);
  // ENCODER A
  PA4.init(GPIOA, GPIO_PIN_4);
  PC3.init(GPIOC, GPIO_PIN_3);
  PF10.init(GPIOF, GPIO_PIN_10);
  PI0.init(GPIOI, GPIO_PIN_0);
  // ENCODER B
  PF0.init(GPIOF, GPIO_PIN_0);
  PE4.init(GPIOE, GPIO_PIN_4);
  PE5.init(GPIOE, GPIO_PIN_5);
  PE6.init(GPIOE, GPIO_PIN_6);
  // L298N IN1
  PC0.init(GPIOC, GPIO_PIN_0);
  PC4.init(GPIOC, GPIO_PIN_4);
  PI2.init(GPIOI, GPIO_PIN_2);
  PI6.init(GPIOI, GPIO_PIN_6);
  // L298N IN2
  PC1.init(GPIOC, GPIO_PIN_1);
  PC5.init(GPIOC, GPIO_PIN_5);
  PI5.init(GPIOI, GPIO_PIN_5);
  PI7.init(GPIOI, GPIO_PIN_7);
  // Step motor
  PC2.init(GPIOC, GPIO_PIN_2);
  PI9.init(GPIOI, GPIO_PIN_9);
  // CAN
  BSP_CAN_Init();
}

void BSP_defaultTask(void) { time = usTimer.getTime() / 1000000; }

void EXTICallback(uint16_t index) { GPIO::GPIO_EXTICallback(index); }

void uartCallback(UART_HandleTypeDef* phuart) {
  BSP_UART::UART_rxCallback(phuart);
}

void timCallback(TIM_HandleTypeDef* phtim) {
  if (phtim == &htim14) usTimer.update();
}

void c_delay(uint16_t us) { usTimer.delayus(us); }
