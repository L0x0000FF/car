#include "vofa.hpp"
#include <cstdio>
#include <cstring>
#include "string"

Vofa::Vofa() {
  this->transmitStarted = false;
}

void Vofa::init(UART_HandleTypeDef *phuart) {
  this->phuart = phuart;
}

uint8_t Vofa::addPack(Vofa_TxPack_t pack) {
  this->packList.push_back(pack);
  return packList.size();
}

uint8_t Vofa::addPack(void *buffer, Vofa_DataType_e type) {
  this->packList.push_back(Vofa_TxPack_t{buffer, type});
  return packList.size();
}

void Vofa::rmPack(uint8_t index) {
  packList.erase(packList.begin() + index);
}

void Vofa::startTransmit() {
  this->transmitStarted = true;
}

void Vofa::stopTransmit() {
  this->transmitStarted = false;
}

void Vofa::update() {
  if (transmitStarted) {
    uint8_t tmp = packList.size();
    string str("");
    for (uint8_t i = 0; i < tmp; i++) {
      switch (packList[i].type) {
        case VOFA_DATA_INT:
          str += to_string(*(int *) (packList[i].buffer));
          break;
        case VOFA_DATA_FLOAT:
          str += to_string(*(float *) (packList[i].buffer));
          break;
        case VOFA_DATA_BOOL:
          str += to_string(*(bool *) (packList[i].buffer));
          break;
        case VOFA_DATA_CHAR_PTR:
          str += *(char *) (packList[i].buffer);
          break;
        case VOFA_DATA_STRING:
          str += *(string *) (packList[i].buffer);
          break;
        default:
          break;
      }
      if (i == tmp - 1)str += "\n";
      else str += ",";
    }
    HAL_UART_Transmit(phuart, (uint8_t *) str.data(), str.size(),100);
  }
}
