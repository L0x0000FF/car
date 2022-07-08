#include "atgm366h5n.hpp"

ATGM366H5N::ATGM366H5N() {

}

ATGM366H5N::~ATGM366H5N() {

}

void ATGM366H5N::init(UART_HandleTypeDef *phuart) {
  this->phuart = phuart;
}

NEMAData ATGM366H5N::getData() {
  return this->parser.getData();
}
