#ifndef ATGM366H5N_HPP
#define ATGM366H5N_HPP

#include "main.h"
#include "nema_parser.hpp"

class ATGM366H5N {
private:
  UART_HandleTypeDef *phuart;
  NEMAParser parser;
public:
  ATGM366H5N();
  ~ATGM366H5N();
  void init(UART_HandleTypeDef *phuart);
  NEMAData getData();
};


#endif //ATGM366H5N_HPP
