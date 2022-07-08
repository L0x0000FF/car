#include "pwm_motor.hpp"

#include <vector>

std::vector<PWM_Motor*> pwm_motor_list;

PWM_Motor::PWM_Motor() {
  output = 0;
  encoder_cnt = 0;
  speed = 0;
  real_position = 0;
  last_real_position = 0;
  round = 0;
}

void PWM_Motor::init(uint8_t id, TIM_HandleTypeDef* phtim_power,
                     uint32_t power_channel, UsTimer* ptimer, GPIO* in1,
                     GPIO* in2, GPIO* encoder_A, GPIO* encoder_B) {
  this->id = id;
  this->phtim_power = phtim_power;
  this->power_channel = power_channel;
  this->ptimer = ptimer;
  this->in1 = in1;
  this->in2 = in2;
  this->encoder_A = encoder_A;
  this->encoder_B = encoder_B;
  this->encoder_A->regEXTICallback(PWM_Motor_encoder_update);
  in1->high();
  in2->high();
  pwm_motor_list.push_back(this);

  HAL_TIM_PWM_Start(phtim_power, power_channel);
}

void PWM_Motor::setOutput(int output) { this->output = output; }

void PWM_Motor::update() {
  real_position += encoder_cnt;
  dt = (ptimer->getTime() - last_update_time) * 0.000001f;

  // // calc speed & position
  // encoder_cnt = (int)((int16_t)phtim_encoder->Instance->CNT);
  // if (encoder_cnt - last_encoder_cnt > 50000)
  //   round--;  //-32767 -> 32767
  // else if (encoder_cnt - last_encoder_cnt < -50000)
  //   round++;  // 32767 -> -32767
  // real_position = round * 65536 + encoder_cnt;
  speed = encoder_cnt / dt;
  encoder_cnt = 0;

  last_update_time = ptimer->getTime();

  // set output
  if (output == 0) {
    in1->high();
    in2->high();
    __HAL_TIM_SET_COMPARE(phtim_power, power_channel, output);
  } else if (output > 0) {
    in1->high();
    in2->low();
    __HAL_TIM_SET_COMPARE(phtim_power, power_channel, output);
  } else if (output < 0) {
    in1->low();
    in2->high();
    __HAL_TIM_SET_COMPARE(phtim_power, power_channel, -output);
  }
}

void PWM_Motor::PWM_Motor_encoder_update(uint16_t EXTI_line) {
  for (uint8_t i = 0; i < pwm_motor_list.size(); i++) {
    if (pwm_motor_list[i]->encoder_A->pin == EXTI_line)
      pwm_motor_list[i]->updateEncoder();
    break;
  }
}

void PWM_Motor::updateEncoder() {
  if (this->encoder_A->read() == GPIO_PIN_RESET) {
    if (this->encoder_B->read() == GPIO_PIN_RESET) {
      this->encoder_cnt++;
    } else
      this->encoder_cnt--;
  } else {
    if (this->encoder_B->read() == GPIO_PIN_RESET) {
      this->encoder_cnt--;
    } else
      this->encoder_cnt++;
  }

  uint8_t i = 0;
  if (this->id == 1) {
    i = 1;
  } else if (this->id == 2) {
    i = 2;
  } else if (this->id == 3) {
    i = 3;
  } else if (this->id == 4) {
    i = 4;
  }
}
