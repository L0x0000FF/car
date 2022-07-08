/* USER CODE BEGIN Header */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M2_ENCB_Pin GPIO_PIN_4
#define M2_ENCB_GPIO_Port GPIOE
#define M3_ENCB_Pin GPIO_PIN_5
#define M3_ENCB_GPIO_Port GPIOE
#define M4_ENCB_Pin GPIO_PIN_6
#define M4_ENCB_GPIO_Port GPIOE
#define M4_IN2_Pin GPIO_PIN_7
#define M4_IN2_GPIO_Port GPIOI
#define M4_IN1_Pin GPIO_PIN_6
#define M4_IN1_GPIO_Port GPIOI
#define M3_IN2_Pin GPIO_PIN_5
#define M3_IN2_GPIO_Port GPIOI
#define M3_IN1_Pin GPIO_PIN_2
#define M3_IN1_GPIO_Port GPIOI
#define STEPMOTOR_ENA_Pin GPIO_PIN_9
#define STEPMOTOR_ENA_GPIO_Port GPIOI
#define M1_ENCB_Pin GPIO_PIN_0
#define M1_ENCB_GPIO_Port GPIOF
#define M4_ENCA_Pin GPIO_PIN_0
#define M4_ENCA_GPIO_Port GPIOI
#define M4_ENCA_EXTI_IRQn EXTI0_IRQn
#define M3_ENCA_Pin GPIO_PIN_10
#define M3_ENCA_GPIO_Port GPIOF
#define M3_ENCA_EXTI_IRQn EXTI15_10_IRQn
#define M1_IN1_Pin GPIO_PIN_0
#define M1_IN1_GPIO_Port GPIOC
#define M1_IN2_Pin GPIO_PIN_1
#define M1_IN2_GPIO_Port GPIOC
#define STEPMOTOR_DIR_Pin GPIO_PIN_2
#define STEPMOTOR_DIR_GPIO_Port GPIOC
#define M2_ENCA_Pin GPIO_PIN_3
#define M2_ENCA_GPIO_Port GPIOC
#define M2_ENCA_EXTI_IRQn EXTI3_IRQn
#define M1_ENCA_Pin GPIO_PIN_4
#define M1_ENCA_GPIO_Port GPIOA
#define M1_ENCA_EXTI_IRQn EXTI4_IRQn
#define M2_IN1_Pin GPIO_PIN_4
#define M2_IN1_GPIO_Port GPIOC
#define M2_IN2_Pin GPIO_PIN_5
#define M2_IN2_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
