#include "hal.h"

#include <stdio.h>

#include "pwm_motor.hpp"
#include "sbus.hpp"
#include "servo.hpp"
#include "step_motor.hpp"
#include "can_motor.hpp"

// externs
extern uint8_t bsp_inited;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;
extern BSP_UART uart1;
extern BSP_UART uart3;
extern UsTimer usTimer;

// EXTI PINS FOR ENCODER A
extern GPIO PA4;
extern GPIO PC3;
extern GPIO PF10;
extern GPIO PI0;
// NORMAL PINS FOR ENCODER B
extern GPIO PF0;
extern GPIO PE4;
extern GPIO PE5;
extern GPIO PE6;
// L298N IN1
extern GPIO PC0;
extern GPIO PC4;
extern GPIO PI2;
extern GPIO PI6;
// L298N IN2
extern GPIO PC1;
extern GPIO PC5;
extern GPIO PI5;
extern GPIO PI7;
// Step motor
extern GPIO PC2;  // DIR
extern GPIO PI9;  // ENA

// Devices
// PWM_Motor M1;
// PWM_Motor M2;
// PWM_Motor M3;
// PWM_Motor M4;
Servo yaw_servo;
Servo gripper;
Step_Motor push_pull;
CAN_Motor M1;
CAN_Motor M2;
CAN_Motor M3;
CAN_Motor M4;

uint8_t hal_inited = 0;

void HAL_init(void) {
  while (!bsp_inited)
    ;
  rc.init(&uart1);
  // M1.init(1,&htim2, TIM_CHANNEL_1, &usTimer, &PC0, &PC1, &PA4, &PF0);
  // M2.init(2,&htim2, TIM_CHANNEL_2, &usTimer, &PC4, &PC5, &PC3, &PE4);
  // M3.init(3,&htim2, TIM_CHANNEL_3, &usTimer, &PI2, &PI5, &PF10, &PE5);
  // M4.init(4,&htim2, TIM_CHANNEL_4, &usTimer, &PI6, &PI7, &PI0, &PE6);
  yaw_servo.init(&htim5,TIM_CHANNEL_1);
	gripper.init(&htim5,TIM_CHANNEL_2);
  push_pull.init(&htim9,TIM_CHANNEL_1,&PI9,&PC2);
  CAN_Motor::CAN_Motor_Driver_Init();

  can_motor_config m1_config;
  m1_config.bsp_can_index = 0;
  m1_config.motor_model = MODEL_3508;
  m1_config.motor_set_id = 1;
  m1_config.position_fdb_model = MOTOR_FDB;
  m1_config.speed_fdb_model = MOTOR_FDB;
  m1_config.output_model = MOTOR_OUTPUT_REVERSE;
  m1_config.PID_Kp = 3;
  m1_config.PID_Ki = 0;
  m1_config.PID_Kd = 0;
  m1_config.PID_output_max = 10000;
  m1_config.PID_error_max = 2000;

  can_motor_config m2_config;
  can_motor_config m3_config;
  can_motor_config m4_config;

  M1.init(&m1_config);
  // M2.init(&m2_config);
  // M3.init(&m3_config);
  // M4.init(&m4_config);
}

void HAL_defaultTask(void) {
  CAN_Motor::CAN_Motor_Calc_Send();
}
