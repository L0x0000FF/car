#include "attitude_estimator.hpp"

#include "math.h"
#include "string.h"

AttitudeEstimator attitudeEstimator;

AttitudeEstimator::AttitudeEstimator() {
  memset(&gyro_bias, 0, sizeof(Vector3f));
  memset(&angle, 0, sizeof(Vector3f));
  memset(&gyro_fixed, 0, sizeof(Vector3f));
  memset(&quaternion, 0, sizeof(Vector4f));
  quaternion.w = 1.0f;
  this->task_attributes.name = "AttitudeEstimatorTask";
  this->task_attributes.stack_size = 128 * 4;
  this->task_attributes.priority = (osPriority_t)osPriorityNormal;
}

void AttitudeEstimator::init(MPU6050* imu, UsTimer* timer) {
  this->imu = imu;
  this->timer = timer;
  this->integralFBx = 0.0f;
  this->integralFBy = 0.0f;
  this->integralFBz = 0.0f;
  this->twoKp = 5.0f;
  this->twoKi = 0.0002f;
  // calibration
  while (imu->gyro.x == 0 && imu->gyro.y == 0 && imu->gyro.z == 0)
    ;
  for (int i = 0; i < 1000; i++) {
    gyro_bias.x += imu->gyro.x;
    gyro_bias.y += imu->gyro.y;
    gyro_bias.z += imu->gyro.z;
  }
  gyro_bias.x /= 1000.0f;
  gyro_bias.y /= 1000.0f;
  gyro_bias.z /= 1000.0f;

  this->task_handle = osThreadNew(attr_run, NULL, &(this->task_attributes));
}

void AttitudeEstimator::update(float dt) {
  gyro_fixed.x = (imu->gyro.x - gyro_bias.x) * DEG2RAD;
  gyro_fixed.y = (imu->gyro.y - gyro_bias.y) * DEG2RAD;
  gyro_fixed.z = (imu->gyro.z - gyro_bias.z) * DEG2RAD;

  // MahonyAHRS
  float recipNorm;
  float halfvx, halfvy, halfvz;
  float halfex, halfey, halfez;
  float qa, qb, qc;

  // Compute feedback only if accelerometer measurement valid (avoids NaN in
  // accelerometer normalisation)
  if (!((imu->accel.x == 0.0f) && (imu->accel.y == 0.0f) &&
        (imu->accel.z == 0.0f))) {
    // Normalise accelerometer measurement
    recipNorm =
        invSqrt(imu->accel.x * imu->accel.x + imu->accel.y * imu->accel.y +
                imu->accel.z * imu->accel.z);
    imu->accel.x *= recipNorm;
    imu->accel.y *= recipNorm;
    imu->accel.z *= recipNorm;

    // Estimated direction of gravity and vector perpendicular to magnetic
    // flux
    halfvx = quaternion.x * quaternion.z - quaternion.w * quaternion.y;
    halfvy = quaternion.w * quaternion.x + quaternion.y * quaternion.z;
    halfvz = quaternion.w * quaternion.w - 0.5f + quaternion.z * quaternion.z;

    // Error is sum of cross product between estimated and measured
    // direction of gravity
    halfex = (imu->accel.y * halfvz - imu->accel.z * halfvy);
    halfey = (imu->accel.z * halfvx - imu->accel.x * halfvz);
    halfez = (imu->accel.x * halfvy - imu->accel.y * halfvx);

    // Compute and apply integral feedback if enabled
    if (twoKi > 0.0f) {
      integralFBx += twoKi * halfex * dt;  // integral error scaled by Ki
      integralFBy += twoKi * halfey * dt;
      integralFBz += twoKi * halfez * dt;
      gyro_fixed.x += integralFBx;  // apply integral feedback
      gyro_fixed.y += integralFBy;
      gyro_fixed.z += integralFBz;
    } else {
      integralFBx = 0.0f;  // prevent integral windup
      integralFBy = 0.0f;
      integralFBz = 0.0f;
    }

    // Apply proportional feedback
    gyro_fixed.x += twoKp * halfex;
    gyro_fixed.y += twoKp * halfey;
    gyro_fixed.z += twoKp * halfez;
  }

  // Integrate rate of change of quaternion
  gyro_fixed.x *= (0.5f * dt);  // pre-multiply common factors
  gyro_fixed.y *= (0.5f * dt);
  gyro_fixed.z *= (0.5f * dt);
  qa = quaternion.w;
  qb = quaternion.x;
  qc = quaternion.y;
  quaternion.w +=
      (-qb * gyro_fixed.x - qc * gyro_fixed.y - quaternion.z * gyro_fixed.z);
  quaternion.x +=
      (qa * gyro_fixed.x + qc * gyro_fixed.z - quaternion.z * gyro_fixed.y);
  quaternion.y +=
      (qa * gyro_fixed.y - qb * gyro_fixed.z + quaternion.z * gyro_fixed.x);
  quaternion.z += (qa * gyro_fixed.z + qb * gyro_fixed.y - qc * gyro_fixed.x);

  // Normalise quaternion
  recipNorm =
      invSqrt(quaternion.w * quaternion.w + quaternion.x * quaternion.x +
              quaternion.y * quaternion.y + quaternion.z * quaternion.z);
  quaternion.w *= recipNorm;
  quaternion.x *= recipNorm;
  quaternion.y *= recipNorm;
  quaternion.z *= recipNorm;

  // Euler
  angle.x = atan2(
      2 * (quaternion.w * quaternion.x + quaternion.y * quaternion.z),
      1 - 2 * (quaternion.x * quaternion.x + quaternion.y * quaternion.y));
  angle.y =
      asin(2 * (quaternion.w * quaternion.y - quaternion.z * quaternion.x));
  angle.z = atan2(
      2 * (quaternion.w * quaternion.z + quaternion.x * quaternion.y),
      1 - 2 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
}

void AttitudeEstimator::attr_run(void* args) {
  uint32_t last_update_time = attitudeEstimator.timer->getTime();
  for (;;) {
    attitudeEstimator.update(
        0.000001f * (attitudeEstimator.timer->getTime() - last_update_time));
    last_update_time = attitudeEstimator.timer->getTime();
		osDelay(2);
  }
}

float invSqrt(float x) {
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (1.5f - (halfx * y * y));
  return y;
}
