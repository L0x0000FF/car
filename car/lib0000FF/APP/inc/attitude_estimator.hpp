#ifndef ATTITUDE_ESTIMATOR_HPP
#define ATTITUDE_ESTIMATOR_HPP

#include "mpu6050.hpp"
#include "structs.h"
#include "usTimer.h"
// FreeRTOS includes
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "task.h"

#define pi 3.1415926f
#define RAD2DEG (180.0f / pi)
#define DEG2RAD (pi / 180.0f)

class AttitudeEstimator {
 private:
  MPU6050* imu;
  UsTimer* timer;
  float integralFBx;
  float integralFBy;
  float integralFBz;
  // parameters
  float twoKp;
  float twoKi;
  // task configs
  osThreadId_t task_handle;
  osThreadAttr_t task_attributes;

 public:
  Vector3f angle;
  Vector3f gyro_bias;
  Vector3f gyro_fixed;
  Vector4f quaternion;
  AttitudeEstimator();
  void init(MPU6050* imu, UsTimer* timer);
  void update(float dt);
  static void attr_run(void* args);
};

float invSqrt(float x);

extern AttitudeEstimator attitudeEstimator;

#endif
