#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "bsp_i2c.h"
#include "main.h"
#include "structs.h"

// Register ADDR
#define ADDR_MPU6050 0xD0          // The address of the device
#define REG_MPU6050_WHO_AM_I 0X75  // Device ID register
#define REG_MPU6050_PWR_MNG1 0x6B  // Power manage register1
#define REG_MPU6050_PWR_MNG2 0x6C  // Power manage register2
#define REG_MPU6050_GYRO_CFG 0X1B  // Config registers:Config full scale
#define REG_MPU6050_ACCEL_CFG 0X1C
#define REG_MPU6050_SAMPLE_RATE 0X19  // Sample rate register
#define REG_MPU6050_USER_CTRL 0X6A    // User control register
#define REG_MPU6050_FIFO_EN 0X23      // FIFO enable register
#define REG_MPU6050_INTBP_CFG 0X37    // Interruption config register
#define REG_MPU6050_INT_EN 0X38       // Interruption enable register
#define REG_MPU6050_CFG 0X1A          // Config register
// Acceleration
#define REG_MPU6050_ACCEL_X_H 0X3B  // H->High 8,L->Low 8
#define REG_MPU6050_ACCEL_X_L 0X3C
#define REG_MPU6050_ACCEL_Y_H 0X3D
#define REG_MPU6050_ACCEL_Y_L 0X3E
#define REG_MPU6050_ACCEL_Z_H 0X3F
#define REG_MPU6050_ACCEL_Z_L 0X40
// Temperature
#define REG_MPU6050_TEMP_H 0X41
#define REG_MPU6050_TEMP_L 0X42
// Gyro
#define REG_MPU6050_GYRO_X_H 0X43
#define REG_MPU6050_GYRO_X_L 0X44
#define REG_MPU6050_GYRO_Y_H 0X45
#define REG_MPU6050_GYRO_Y_L 0X46
#define REG_MPU6050_GYRO_Z_H 0X47
#define REG_MPU6050_GYRO_Z_L 0X48

class MPU6050 {
 private:
  BSP_I2C *phi2c;
  uint8_t addr;
  void writeReg(uint8_t regAddr, uint8_t data);
  void readReg(uint8_t regAddr, uint8_t *data, uint8_t len);
  uint8_t readReg8(uint8_t regAddr);

 public:
  Vector3f gyro;
  Vector3f accel;
  uint16_t temp;
  MPU6050();
  void init(BSP_I2C *phi2c, uint8_t addr = ADDR_MPU6050);
  void reset();
  void update();
};

#endif  // MPU6050_HPP
