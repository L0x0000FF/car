/* 基于can_send/can_recv 创建的标准化的电机控制机制*/
#ifndef CAN_MOTOR_HPP
#define CAN_MOTOR_HPP

#include "pid.h"
#include "stdint.h"
#include "circular_queue.h"

enum Motor_Model_e { MODEL_3508 = 0, MODEL_2006, MODEL_6020 };
enum Motor_FDB_Model_e { MOTOR_FDB = 0, OTHER_FDB };

enum Motor_OUTPUT_Model_e {
  MOTOR_OUTPUT_NORMAL = 0,
  MOTOR_OUTPUT_REVERSE
};  //是否输出反转

enum MOTOR_ENABLE { MOTOR_STOP = 0, MOTOR_ENABLE };

typedef struct can_motor_config_t {
  uint8_t bsp_can_index;
  uint8_t motor_set_id;  //电调上通过闪灯次数确定的id
  enum Motor_Model_e motor_model;
  // PID config
  float PID_Kp;
  float PID_Ki;
  float PID_Kd;
  float PID_output_max;  // absolute value
  float PID_error_max;

  enum Motor_FDB_Model_e position_fdb_model;
  enum Motor_FDB_Model_e speed_fdb_model;
  enum Motor_OUTPUT_Model_e output_model;
  float* speed_fdb;  // OTHER_FDB模式的ref指针
  float* position_fdb;
} can_motor_config;

class CAN_Motor {
 public:
  can_motor_config config;
  enum MOTOR_ENABLE enable;
  short fdbPosition;       //电机的编码器反馈值
  short last_fdbPosition;  //电机上次的编码器反馈值
  short fdbSpeed;          //电机反馈的转速/rpm
  short electric_current;  //电机实际转矩电流
  short round;             //电机转过的圈数
  uint8_t temperature;     //电机温度

  float real_position;       //过零处理后的角度，单位度
  float real_position_8192;  //过零处理后的电机转子位置 (0-8192)
  float last_real_position_8192;  //上次真实转过的角度 (0-8192)
  PID motor_controller;           //控制器

  float line_speed;                //线速度（m/s，根据角速度算出）
  circular_queue* position_queue;  //计算角速度的循环队列
  float position_sum;              //队列中所有值的和
  float velocity;  //用电机编码器计算出来的角速度（单位：度每秒）

  CAN_Motor();
  void init(can_motor_config* config);
  static void CAN_Motor_Driver_Init();
  static void CAN_Motor_Calc_Send();
};

#endif
