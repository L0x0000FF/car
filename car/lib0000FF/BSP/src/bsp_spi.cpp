#include "bsp_spi.h"

SPI::SPI(SPI_HandleTypeDef* phspi) {
  this->phspi = phspi;
}

SPI::~SPI() {}

void SPI::update(){
  if (issues.getLength() != 0) {
    SPI_Issue issue_current = issues.pop();
    issue_current.pin_CS->low();
    if(issue_current.type == TX)
    issue_current.pin_CS->high();
  }
}

void SPI::transmit(GPIO* pin_CS, uint8_t* pData) {
  //this->issues.add({TX, pin_CS, nullptr, pData});
}

void SPI::receive(GPIO* pin_CS, uint8_t* pData) {
  //this->issues.add({TX, pin_CS, pData, nullptr});
}

void SPI::transmitReceive(GPIO* pin_CS, uint8_t* pData_tx, uint8_t* pData_rx) {
  //this->issues.add({TX, pin_CS, pData_tx, pData_rx});
}
