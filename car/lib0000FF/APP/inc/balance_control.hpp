#ifndef BALANCE_CONTORL_HPP
#define BALANCE_CONTORL_HPP

#include "FSi6.hpp"
#include "attitude_estimator.hpp"
#include "pid.h"
#include "pwm_motor.hpp"
#include "structs.h"
// FreeRTOS includes
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "task.h"

class BalanceControl {
 private:
  // Devices
  AttitudeEstimator* att;
  FSi6* rc;
  PWM_Motor* motor_L;
  PWM_Motor* motor_R;
  // PID
  PID angle_pid;
  PID speed_pid;
  float balance_bias;
  // task configs
  osThreadId_t task_handle;
  osThreadAttr_t task_attributes;

 public:
  BalanceControl();
  void init(AttitudeEstimator* att, FSi6* rc, PWM_Motor* motor_L,
            PWM_Motor* motor_R, float angle_kp = 0.0f, float angle_ki = 0.0f,
            float angle_kd = 0.0f, float angle_outputMax = 0.0f,
            float angle_errorMax = 0.0f, float speed_kp = 0.0f,
            float speed_ki = 0.0f, float speed_kd = 0.0f,
            float speed_outputMax = 0.0f, float speed_errorMax = 0.0f);
  void tunning(float angle_kp = 0.0f, float angle_ki = 0.0f,
               float angle_kd = 0.0f, float speed_kp = 0.0f,
               float speed_ki = 0.0f, float speed_kd = 0.0f);
  static void balanceCtrl_run(void* args);
};

extern BalanceControl balanceControl;

#endif
