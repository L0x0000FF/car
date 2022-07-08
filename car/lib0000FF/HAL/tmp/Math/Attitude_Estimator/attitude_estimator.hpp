#ifndef ATTITUDE_ESTIMATOR_HPP
#define ATTITUDE_ESTIMATOR_HPP

#include "mpu6050.hpp"
#include "sys_timer.hpp"
#include "vector"
#include "vector3f.hpp"

using namespace std;

class AttitudeEstimator {
 private:
  MPU6050* imu;
  SysTimer* timer;
  uint64_t last_update_time;
  bool isCalibrating;
  Vector3f gyro_bias;
  float accel_g;

 public:
  Vector3f angle_gyro;
  Vector3f angle_accel;
  AttitudeEstimator();
  AttitudeEstimator(MPU6050* imu, SysTimer* timer);
  void init(MPU6050* imu, SysTimer* timer);
  void update();
  void calibrate();
  void estimate();
};

class AttrKalman{
  public:
  float A[2][2];
  float P[2][2];
  float Q[2][2];
  float R[2][2];
  float K[2][2];
};

#endif  // ATTITUDE_ESTIMATOR_HPP
