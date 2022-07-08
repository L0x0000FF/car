#ifndef BSP_CAN_H
#define BSP_CAN_H

#include "main.h"

/*--------------------------------------------------bsp_can--------------------------------------------------*/
/**
 * @brief      :can通信过滤器的最大数目
 * @attention  :此宏定义按照标准帧定义，无需更改
 */
#define FILTER_MAX_CNT (4 * 14)

/**
 * @brief      :主控共使用（拥有）的can总线数量
 * @attention  :如果使用A板或C板，此处值为2
 *              如果使用stm32F7系列主控，此处值为3，且bsp_can.c中的内容也需要更改，此时应询问电控组长，禁止自行更改
 */
#define DEVICE_CAN_CNT 2

/**
 * @brief      :can线上能用到的最大的ID号
 * @attention  :一般用不到，无需更改
 */
#define ID_MAX 0x07FF

/**
 * @brief      :未使用can通信过滤器时候的过滤器填充值
 * @attention  :固定值，禁止更改
 */
#define ID_NOTSET 0x800

typedef void (*can_rx_callback)(uint8_t can_id, uint32_t identifier,
                                uint8_t* data, uint32_t len);

void BSP_CAN_Init();
void BSP_CAN_AddFilter(uint8_t can_id, uint16_t filter);
void BSP_CAN_RemoveFilter(uint8_t can_id, uint16_t filter);
void BSP_CAN_Send(uint8_t can_id, uint16_t identifier, uint8_t* data,
                  uint32_t len);
void BSP_CAN_RegisterRxCallback(uint8_t can_id, can_rx_callback func);
void BSP_CAN_FifoMsg_Callback(CAN_HandleTypeDef* hcan, uint32_t fifo);

#endif
