#include "bsp_i2c.h"

BSP_I2C::BSP_I2C(void) { this->isBusy = false; }

#ifdef USE_SOFT_I2C
void BSP_I2C::init(GPIO* SCL, GPIO* SDA, UsTimer* timer) {
  this->SCL = SCL;
  this->SDA = SDA;
  this->timer = timer;
}

void BSP_I2C::SDA_out() {
  GPIO_InitTypeDef initStruct;
  initStruct.Pin = this->SDA->pin;
  initStruct.Mode = GPIO_MODE_OUTPUT_OD;
  initStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(this->SDA->pGPIO, &initStruct);
}

void BSP_I2C::SDA_in() {
  GPIO_InitTypeDef initStruct;
  initStruct.Pin = this->SDA->pin;
  initStruct.Mode = GPIO_MODE_INPUT;
  initStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(this->SDA->pGPIO, &initStruct);
}

// SOFT_I2C IIC 延时函数
void BSP_I2C::delay(void) { timer->delayus(5); }

//产生IIC起始信号
void BSP_I2C::start() {
  SDA_out();  // sda线输出
  this->SDA->high();
  this->SCL->high();
  delay();
  this->SDA->low();  // START:when CLK is high,DATA change form high to low
  this->SCL->low();  //钳住I2C总线，准备发送或接收数据
}

//产生IIC停止信号
void BSP_I2C::stop() {
  SDA_out();  // sda线输出
  this->SCL->low();
  this->SDA->low();  // STOP:when CLK is high DATA change form low to high
  delay();
  this->SCL->high();
  this->SDA->high();  //发送I2C总线结束信号
  delay();
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t BSP_I2C::waitAck() {
  uint8_t ucErrTime = 0;
  SDA_out();
  this->SDA->high();
  SDA_in();  // SDA设置为输入
  delay();
  this->SCL->high();
  delay();
  while (this->SDA->read() == GPIO_PIN_SET) {
    ucErrTime++;
    if (ucErrTime > 250) {
      stop();
      return 1;
    }
  }
  this->SCL->low();  //时钟输出0
  return 0;
}

//产生ACK应答
void BSP_I2C::ack() {
  SDA_out();
  this->SCL->low();
  this->SDA->low();
  delay();
  this->SCL->high();
  delay();
  this->SCL->low();
}

//不产生ACK应答
void BSP_I2C::nack() {
  SDA_out();
  this->SCL->low();
  this->SDA->high();
  delay();
  this->SCL->high();
  delay();
  this->SCL->low();
}

// IIC发送一个字节
void BSP_I2C::sendByte(uint8_t byte) {
  uint8_t t;
  SDA_out();
  this->SCL->low();  //拉低时钟开始数据传输
  for (t = 0; t < 8; t++) {
    if (byte & 0x80)
      this->SDA->high();
    else
      this->SDA->low();
    byte <<= 1;
    delay();
    this->SCL->high();
    delay();
    this->SCL->low();
  }
}

//读1个字节
uint8_t BSP_I2C::readByte() {
  unsigned char i, result = 0;
  SDA_in();  // SDA设置为输入
  for (i = 0; i < 8; i++) {
    this->SCL->low();
    delay();
    this->SCL->high();
    result <<= 1;
    if (this->SDA->read() == GPIO_PIN_SET) result++;
    delay();
  }
  this->SCL->low();
  return result;
}
#endif

#ifdef USE_THIRD_PARTY_SOFT_I2C
void BSP_I2C::init(GPIO* SCL, GPIO* SDA) {
  this->hi2c.SCLPort = SCL->pGPIO;
  this->hi2c.SDAPort = SDA->pGPIO;
  this->hi2c.SCLPin = SCL->pin;
  this->hi2c.SDAPin = SDA->pin;
  softI2cInit(&(this->hi2c));
}
#endif

#ifdef USE_HW_I2C
void BSP_I2C::init(I2C_HandleTypeDef* phi2c, UsTimer* timer) {}
#endif

uint8_t BSP_I2C::writeLen(uint8_t devAddr, uint8_t addr, uint8_t* data,
                          uint16_t length) {
  while (isBusy)
    ;
  isBusy = true;
#ifdef USE_SOFT_I2C
  uint8_t i;
  start();
  sendByte((devAddr << 1) | 0);  //发送器件地址+写命令
  if (waitAck()) {               //等待应答
    stop();
    isBusy = false;
    return 1;
  }
  sendByte(addr);   //写寄存器地址
  if (waitAck()) {  //等待应答
    stop();
    isBusy = false;
    return 1;
  }
  for (i = 0; i < length; i++) {
    sendByte(data[i]);  //发送数据
    if (waitAck()) {    //等待ACK
      stop();
      isBusy = false;
      return 1;
    }
  }
  stop();
#endif
#ifdef USE_THIRD_PARTY_SOFT_I2C
  SFIIC_Mem_Write(&hi2c,devAddr,addr,1,data,length,100);
#endif
#ifdef USE_HW_I2C
  HAL_I2C_Mem_Write(phi2c, devAddr << 1, addr, I2C_MEMADD_SIZE_8BIT, data,
                    length, HAL_MAX_DELAY);
#endif
  isBusy = false;
  return 0;
}

uint8_t BSP_I2C::readLen(uint8_t devAddr, uint8_t addr, uint8_t* data,
                         uint16_t length) {
  while (isBusy)
    ;
  isBusy = true;
#ifdef USE_SOFT_I2C
  start();
  sendByte((devAddr << 1) | 0);  //发送器件地址+写命令
  if (waitAck()) {               //等待应答
    stop();
    isBusy = false;
    return 1;
  }
  sendByte(addr);   //写寄存器地址
  if (waitAck()) {  //等待应答
    stop();
    isBusy = false;
    return 1;
  }
  start();
  sendByte((devAddr << 1) | 1);  //发送器件地址+读命令
  if (waitAck()) {               //等待应答
    stop();
    isBusy = false;
    return 1;
  }
  while (length) {
    if (length == 1) {
      *data = readByte();  //读数据,发送nACK
      nack();
    } else {
      *data = readByte();  //读数据,发送ACK
      ack();
    }
    length--;
    data++;
  }
  stop();  //产生一个停止条件
#endif
#ifdef USE_THIRD_PARTY_SOFT_I2C
  SFIIC_Mem_Read(&hi2c, devAddr, addr, 1, data, length, 100);
#endif
#ifdef USE_HW_I2C
  HAL_I2C_Mem_Read(phi2c, devAddr << 1, addr, I2C_MEMADD_SIZE_8BIT, data,
                   length, HAL_MAX_DELAY);
#endif
  isBusy = false;
  return 0;
}

uint8_t BSP_I2C::writeOneByte(uint8_t devAddr, uint8_t addr, uint8_t data) {
  writeLen(devAddr, addr, &data, 1);
  return 0;
}

uint8_t BSP_I2C::readOneByte(uint8_t devAddr, uint8_t addr) {
  uint8_t result = 0;
  readLen(devAddr, addr, &result, 1);
  return result;
}
