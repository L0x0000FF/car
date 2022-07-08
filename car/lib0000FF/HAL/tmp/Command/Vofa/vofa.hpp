#ifndef VOFA_HPP
#define VOFA_HPP

#include "main.h"
#include "vector"

using namespace std;

typedef enum{
  VOFA_DATA_INT,
  VOFA_DATA_FLOAT,
  VOFA_DATA_BOOL,
  VOFA_DATA_CHAR_PTR,
  VOFA_DATA_STRING
}Vofa_DataType_e;

typedef struct {
  void* buffer;
  Vofa_DataType_e type;
}Vofa_TxPack_t;

class Vofa{
private:
  UART_HandleTypeDef* phuart;
  vector<Vofa_TxPack_t> packList;
  bool transmitStarted;
public:
  Vofa();
  void init(UART_HandleTypeDef* phuart);
  uint8_t addPack(Vofa_TxPack_t pack);
  uint8_t addPack(void* buffer,Vofa_DataType_e type);
  void rmPack(uint8_t index);
  void startTransmit();
  void stopTransmit();
  void update();
};


#endif //VOFA_HPP
