#ifndef BSP_SPI_H
#define BSP_SPI_H

#include "bsp_gpio.h"
#include "main.h"

typedef enum{
  RX,
  TX,
  RxTx
}SPI_Issue_Type_e;

typedef struct SPI_Issue{
  SPI_Issue_Type_e type;
  GPIO* pin_CS;
  uint8_t* dataRx;
  uint8_t* dataTx;
};

class SPI {
 private:
  SPI_HandleTypeDef* phspi;
  Queue<SPI_Issue> issues;
 public:
  SPI(SPI_HandleTypeDef* phspi);
  ~SPI();

  void update();
  void transmit(GPIO* pin_CS,uint8_t* pData);
  void receive(GPIO* pin_CS,uint8_t* pData);
  void transmitReceive(GPIO* pin_CS,uint8_t* pData_tx,uint8_t* pData_rx);

};

#endif
