#include "balance_control.hpp"

BalanceControl balanceControl;

BalanceControl::BalanceControl() {
  this->task_attributes.name = "BalanceCtrlTask";
  this->task_attributes.stack_size = 128 * 4;
  this->task_attributes.priority = (osPriority_t)osPriorityNormal;
  balance_bias = 0.03f;
}

void BalanceControl::init(AttitudeEstimator* att, FSi6* rc, PWM_Motor* motor_L,
                          PWM_Motor* motor_R, float angle_kp, float angle_ki,
                          float angle_kd, float angle_outputMax,
                          float angle_errorMax, float speed_kp, float speed_ki,
                          float speed_kd, float speed_outputMax,
                          float speed_errorMax) {
  PID_init(&angle_pid, angle_kp, angle_ki, angle_kd, angle_outputMax,
           angle_errorMax);
  PID_init(&speed_pid, speed_kp, speed_ki, speed_kd, speed_outputMax,
           speed_errorMax);
  this->att = att;
  this->rc = rc;
  this->motor_L = motor_L;
  this->motor_R = motor_R;

  this->task_handle =
      osThreadNew(balanceCtrl_run, NULL, &(this->task_attributes));
}

void BalanceControl::tunning(float angle_kp, float angle_ki, float angle_kd,
                             float speed_kp, float speed_ki, float speed_kd) {
  angle_pid.Kp = angle_kp;
  angle_pid.Ki = angle_ki;
  angle_pid.Kd = angle_kd;
  speed_pid.Kp = speed_kp;
  speed_pid.Kp = speed_ki;
  speed_pid.Kp = speed_kd;
}

void BalanceControl::balanceCtrl_run(void* args) {
  for (;;) {
    if (balanceControl.rc->data.ch8 == 1500) {  // manual control
      float vx = (balanceControl.rc->data.ch1 - IBUS_CH_BIAS) * 0.4f;
      float vy = (balanceControl.rc->data.ch0 - IBUS_CH_BIAS) * 0.2f;
      balanceControl.motor_L->setOutput(vx + vy);
      balanceControl.motor_R->setOutput(vx - vy);
    } else if (balanceControl.rc->data.ch8 == 2000) {  // balance control
      // angle pid
      balanceControl.angle_pid.fdb = balanceControl.att->angle.x;
      balanceControl.angle_pid.ref = balanceControl.balance_bias;
      PID_calc(&(balanceControl.angle_pid));
      // speed pid
      balanceControl.speed_pid.fdb = (balanceControl.motor_L->getSpeed() +
                                      balanceControl.motor_R->getSpeed()) *
                                     0.5f;
      if (balanceControl.rc->data.ch1 - IBUS_CH_BIAS < 8 &&
          balanceControl.rc->data.ch1 - IBUS_CH_BIAS > -8)
        balanceControl.speed_pid.ref = 0;
      else
        balanceControl.speed_pid.ref =
            (balanceControl.rc->data.ch1 - IBUS_CH_BIAS) * 1.0f;
      PID_calc(&(balanceControl.speed_pid));
      balanceControl.motor_L->setOutput(
          (balanceControl.angle_pid.output + balanceControl.speed_pid.output));
      balanceControl.motor_R->setOutput(
          (balanceControl.angle_pid.output + balanceControl.speed_pid.output));
    }
    else {  // stop
      balanceControl.motor_L->setOutput(0);
      balanceControl.motor_R->setOutput(0);
    }
    osDelay(2);
  }
}
