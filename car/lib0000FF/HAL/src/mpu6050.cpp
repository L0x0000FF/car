#include "mpu6050.hpp"

#include "stdio.h"
#include "string.h"

MPU6050::MPU6050() { temp = 0; }

void MPU6050::init(BSP_I2C *phi2c, uint8_t addr) {
  this->phi2c = phi2c;
  this->addr = addr;

  uint8_t checkAddr, tmpData, isInited = 0;
  while (!isInited) {
    phi2c->readLen(addr, REG_MPU6050_WHO_AM_I, &checkAddr, 1);
    // HAL_I2C_Mem_Read(phi2c, addr, REG_MPU6050_WHO_AM_I, I2C_MEMADD_SIZE_8BIT,
    //                  &checkAddr, 1, 100);
    if (checkAddr == 104) {
      // power management register 0X6B we should write all 0's to wake the
      // sensor up
      tmpData = 0;
      phi2c->writeOneByte(addr, REG_MPU6050_PWR_MNG1, 0);
      // HAL_I2C_Mem_Write(phi2c, addr, REG_MPU6050_PWR_MNG1,
      // I2C_MEMADD_SIZE_8BIT,
      //                   &tmpData, 1, 100);

      // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
      tmpData = 0x07;
      phi2c->writeOneByte(addr, REG_MPU6050_SAMPLE_RATE, 0x07);
      // HAL_I2C_Mem_Write(phi2c, addr, REG_MPU6050_SAMPLE_RATE,
      //                   I2C_MEMADD_SIZE_8BIT, &tmpData, 1, 100);

      // Set accelerometer configuration in ACCEL_CONFIG Register
      // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
      tmpData = 0x00;
      phi2c->writeOneByte(addr, REG_MPU6050_ACCEL_CFG, 0x00);
      // HAL_I2C_Mem_Write(phi2c, addr, REG_MPU6050_ACCEL_CFG,
      //                   I2C_MEMADD_SIZE_8BIT, &tmpData, 1, 100);

      // Set Gyroscopic configuration in GYRO_CONFIG Register
      // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
      tmpData = 0x00;
      phi2c->writeOneByte(addr, REG_MPU6050_GYRO_CFG, 0x00);
      // HAL_I2C_Mem_Write(phi2c, addr, REG_MPU6050_GYRO_CFG,
      // I2C_MEMADD_SIZE_8BIT,
      //                   &tmpData, 1, 100);
      isInited = 1;
    }
  }

  // this->reset();
  // this->delay(100);
  // this->writeReg(
  //     REG_MPU6050_GYRO_CFG,
  //     3 << 3);  // Set full scale register: Gyro:±2000dps,Accelerometer:±16g
  // this->writeReg(REG_MPU6050_ACCEL_CFG, 3 << 3);
  // this->sampleRate = 50;
  // this->writeReg(REG_MPU6050_SAMPLE_RATE,
  //                this->sampleRate / 1000 - 1);  // Set sample rate:50Hz
  // this->writeReg(REG_MPU6050_CFG, 4);           // Set low pass filter
  // freq:25Hz this->writeReg(REG_MPU6050_INT_EN, 0X00);     // Set
  // interruption:DISABLED this->writeReg(REG_MPU6050_USER_CTRL, 0X00);  // Set
  // I2C master getMode():OFF this->writeReg(REG_MPU6050_INTBP_CFG, 0X80);  //
  // Set port INT:LOW is valid if (this->readReg8(REG_MPU6050_DEVICE_ID) ==
  //     this->addr) {  // Check whether device ID is right
  //   this->writeReg(REG_MPU6050_PWR_MNG1,
  //                  0X01);  // Set CLKSEL:CLK is respect to PLL x axis
  //   this->writeReg(REG_MPU6050_PWR_MNG2, 0X00);  // Start gyro and
  //   accelerometer this->writeReg(REG_MPU6050_SAMPLE_RATE,
  //                  this->sampleRate / 1000 - 1);  // Set sample rate:50Hz
  // } else {
  //   printf("[MPU6050]:Error: Initialization failed");
  // }
}

void MPU6050::writeReg(uint8_t regAddr, uint8_t data) {
  phi2c->writeOneByte(addr, regAddr, data);
  // HAL_I2C_Mem_Write(phi2c, addr, regAddr, I2C_MEMADD_SIZE_8BIT, &data, 1,
  // 100);
}

void MPU6050::readReg(uint8_t regAddr, uint8_t *data, uint8_t len) {
  phi2c->readLen(addr, regAddr, data, len);
  // HAL_I2C_Mem_Read(phi2c, addr, regAddr, I2C_MEMADD_SIZE_8BIT, data, 1, 100);
}

uint8_t MPU6050::readReg8(uint8_t regAddr) {
  // uint8_t result = 0;
  // HAL_I2C_Mem_Read(phi2c, addr, regAddr, I2C_MEMADD_SIZE_8BIT, &result, 1,
  // 100);
  return phi2c->readOneByte(addr, regAddr);
}

void MPU6050::reset() {
  this->writeReg(REG_MPU6050_PWR_MNG1, 0x80);
  
  this->writeReg(REG_MPU6050_PWR_MNG1, 0x00);
}

void MPU6050::update() {
  uint8_t buf[6];
  int16_t tmp;
  // HAL_I2C_Mem_Read(this->phi2c, this->addr, REG_MPU6050_ACCEL_X_H,
  //                  I2C_MEMADD_SIZE_8BIT, buf, 6, 100);
  phi2c->readLen(addr, REG_MPU6050_ACCEL_X_H, buf, 6);
  tmp = (((int16_t)buf[0]) << 8) | buf[1];
  this->accel.x = tmp / 16384.0f;
  tmp = (((int16_t)buf[2]) << 8) | buf[3];
  this->accel.y = tmp / 16384.0f;
  tmp = (((int16_t)buf[4]) << 8) | buf[5];
  this->accel.z = tmp / 16384.0f;
  // HAL_I2C_Mem_Read(this->phi2c, this->addr, REG_MPU6050_GYRO_X_H,
  //                  I2C_MEMADD_SIZE_8BIT, buf, 6, 100);
  phi2c->readLen(addr, REG_MPU6050_GYRO_X_H, buf, 6);
  tmp = (((int16_t)buf[0]) << 8) | buf[1];
  this->gyro.x = tmp / 131.0f;
  tmp = (((int16_t)buf[2]) << 8) | buf[3];
  this->gyro.y = tmp / 131.0f;
  tmp = (((int16_t)buf[4]) << 8) | buf[5];
  this->gyro.z = tmp / 131.0f;
  // HAL_I2C_Mem_Read(this->phi2c, this->addr, REG_MPU6050_TEMP_H,
  //                  I2C_MEMADD_SIZE_8BIT, buf, 2, 100);
  phi2c->readLen(addr, REG_MPU6050_TEMP_H, buf, 2);
  this->temp = (((int16_t)buf[0]) << 8) | buf[1];
}
