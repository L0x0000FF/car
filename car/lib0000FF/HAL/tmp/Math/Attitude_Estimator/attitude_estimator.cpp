#include "attitude_estimator.hpp"
#include "statistic.hpp"

float dt;

AttitudeEstimator::AttitudeEstimator() {
  this->isCalibrating = true;
}

AttitudeEstimator::AttitudeEstimator(MPU6050 *imu, SysTimer *timer) {
  init(imu, timer);
}

void AttitudeEstimator::init(MPU6050 *imu, SysTimer *timer) {
  this->accel_g = 0.0f;
  this->imu = imu;
  this->timer = timer;
  this->last_update_time = timer->getTime();
}

void AttitudeEstimator::update() {
  if (isCalibrating)
    calibrate();
  else
    estimate();
}

void AttitudeEstimator::calibrate() {
  static uint16_t cali_cnt = 0;
  gyro_bias.x += imu->gyro.x;
  gyro_bias.y += imu->gyro.y;
  gyro_bias.z += imu->gyro.z;
  accel_g += imu->accel.norm();
  cali_cnt++;
  if (cali_cnt > 20) {
    gyro_bias.x /= 20;
    gyro_bias.y /= 20;
    gyro_bias.z /= 20;
    accel_g /= 20;
    isCalibrating = false;
  }
}

void AttitudeEstimator::estimate() {
  dt = 0.000001f * (timer->getTime() - last_update_time);
  for (uint8_t i = 0; i < 3; i++) {
    angle_gyro[i] += (imu->gyro[i] - gyro_bias[i]) * dt;
  }
	angle_accel.x = atanf(imu->accel.y / imu->accel.z) * 57.2957795131f;
  angle_accel.y = asinf(-imu->accel.x / accel_g) * 57.2957795131f;
  last_update_time = timer->getTime();
}
