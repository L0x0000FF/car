#include "app.h"

#include <stdio.h>
#include <string.h>

#include "bsp_uart.h"
#include "can_motor.hpp"
#include "hal.h"
#include "pwm_motor.hpp"
#include "sbus.hpp"
#include "servo.hpp"
#include "step_motor.hpp"

#define GRIPPER_CLOSE 60.0f
#define GRIPPER_OPEN 40.0f
//底盘结构定义
// the radius of wheel(mm)，轮子半径
#define CHASSIS_RADIUS 71  // 71.25
// the perimeter of wheel(mm)，轮子周长
#define CHASSIS_PERIMETER 448  // 71.25*2pi
// wheel track distance(mm)，轮距
#define CHASSIS_WHEELTRACK 340
// wheelbase distance(mm)，轴距
#define CHASSIS_WHEELBASE 340
// gimbal is relative to chassis center x axis
// offset(mm)，云台相对于底盘中心的偏移，往右为正
#define CHASSIS_ROTATE_X_OFFSET 0
// gimbal is relative to chassis center y axis
// offset(mm)，云台相对于底盘中心的偏移，往前为正
#define CHASSIS_ROTATE_Y_OFFSET 0
// the deceleration ratio of chassis motor，底盘电机减速比
#define CHASSIS_MOTOR_DECELE_RATIO 14.0f
#define RADIAN_COEF 57.3f  // 180°/pi

// APPs

// externs
// extern PWM_Motor M1;
// extern PWM_Motor M2;
// extern PWM_Motor M3;
// extern PWM_Motor M4;
extern Servo yaw_servo;
extern Servo gripper;
extern Step_Motor push_pull;
extern CAN_Motor M1;
extern CAN_Motor M2;
extern CAN_Motor M3;
extern CAN_Motor M4;

void APP_init(void) {}

float speed = 0;
int yaw_angle = 0.0f;

float vx = 0;     //左右
float vy = 0;     //前后
float omega = 0;  //旋转

void APP_defaultTask(void) {
  if (rc.data.ch4 == 992) {  //手动模式
    //夹爪
    if (rc.data.ch5 == 192)
      gripper.setAngle(GRIPPER_CLOSE);
    else
      gripper.setAngle(GRIPPER_OPEN);

    // yaw轴舵机
    if (rc.data.ch3 > SBUS_CH_BIAS + 400)
      yaw_angle = 0.0f;
    else if (rc.data.ch3 < SBUS_CH_BIAS - 400)
      yaw_angle = 90.0f;
    yaw_servo.setAngle(yaw_angle);
    // yaw_servo.setAngle(((int16_t)rc.data.ch3 - SBUS_CH_BIAS) * 0.028125f
    // + 45.0f);

    //升降
    if (rc.data.ch2 > SBUS_CH_BIAS + 400)
      speed = 40000;
    else if (rc.data.ch2 < SBUS_CH_BIAS - 400)
      speed = -40000;
    else
      speed = 0;
    push_pull.setSpeed(speed);

    //底盘
    M1.enable = MOTOR_ENABLE;
    M2.enable = MOTOR_ENABLE;
    M3.enable = MOTOR_ENABLE;
    M4.enable = MOTOR_ENABLE;

    vy = (rc.data.ch0 - SBUS_CH_BIAS) * 10;
    vx = (rc.data.ch1 - SBUS_CH_BIAS) * 10;
    float r_x, r_y;
    float mecanum_speed[4];

    r_x = CHASSIS_WHEELTRACK / 2;
    r_y = CHASSIS_WHEELBASE / 2;
    mecanum_speed[0] = vx + vy - omega * (r_x + r_y) / RADIAN_COEF;
    mecanum_speed[1] = vx - vy - omega * (r_x + r_y) / RADIAN_COEF;
    mecanum_speed[2] = -vx - vy - omega * (r_x + r_y) / RADIAN_COEF;
    mecanum_speed[3] = -vx + vy - omega * (r_x + r_y) / RADIAN_COEF;

    M1.motor_controller.ref = mecanum_speed[1];
    M2.motor_controller.ref = mecanum_speed[0];
    M3.motor_controller.ref = mecanum_speed[3];
    M4.motor_controller.ref = mecanum_speed[2];
  } else {  // STOP模式
    M1.enable = MOTOR_STOP;
    M2.enable = MOTOR_STOP;
    M3.enable = MOTOR_STOP;
    M4.enable = MOTOR_STOP;
    push_pull.disable();
  }
}
