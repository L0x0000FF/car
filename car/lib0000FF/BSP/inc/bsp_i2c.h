#ifndef BSP_I2C_H
#define BSP_I2C_H

#include "bsp_gpio.h"
#include "main.h"
#include "usTimer.h"

//#define USE_SOFT_I2C
#define USE_THIRD_PARTY_SOFT_I2C
//#define USE_HW_I2C

#ifdef USE_THIRD_PARTY_SOFT_I2C
#include "softI2c.h"
#endif

class BSP_I2C {
 private:
  bool isBusy;
#ifdef USE_SOFT_I2C
  GPIO* SCL;
  GPIO* SDA;
  UsTimer* timer;
#endif
#ifdef USE_THIRD_PARTY_SOFT_I2C
  SFIIC_HandleTypeDef hi2c;
#endif
#ifdef USE_HW_I2C
  I2C_HandleTypeDef* phi2c;
#endif

 public:
  BSP_I2C(void);
#ifdef USE_SOFT_I2C
  void init(GPIO* SCL, GPIO* SDA, UsTimer* timer);
  // IIC所有操作函数
  void SDA_out(void);
  void SDA_in(void);
  void delay(void);                     // MPU IIC延时函数
  void start(void);                     //发送IIC开始信号
  void stop(void);                      //发送IIC停止信号
  void sendByte(uint8_t txd);           // IIC发送一个字节
  uint8_t readByte();  // IIC读取一个字节
  uint8_t waitAck(void);                // IIC等待ACK信号
  void ack(void);                       // IIC发送ACK信号
  void nack(void);                      // IIC不发送ACK信号
#endif
#ifdef USE_THIRD_PARTY_SOFT_I2C
  void init(GPIO* SCL, GPIO* SDA);
#endif
#ifdef USE_HW_I2C
  void init(I2C_HandleTypeDef* phi2c, UsTimer* timer);
#endif
  uint8_t writeLen(uint8_t devAddr, uint8_t addr, uint8_t* data,
                   uint16_t length);
  uint8_t readLen(uint8_t devAddr, uint8_t addr, uint8_t* data,
                  uint16_t length);
  uint8_t writeOneByte(uint8_t devAddr, uint8_t addr, uint8_t data);
  uint8_t readOneByte(uint8_t devAddr, uint8_t addr);

};

#endif
