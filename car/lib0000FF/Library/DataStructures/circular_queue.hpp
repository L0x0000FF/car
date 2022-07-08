#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CIRCULAR_QUEUE_DEFAULT_LENGTH 5
#define CIRCULAR_QUEUE_ALLOC_LEN 5

template<class T>
class CircularQueue {
private:
  T *pData;
  T *pFront;
  T *pRear;
  uint8_t length;
  uint8_t total_length;
public:
  CircularQueue(uint8_t default_length = CIRCULAR_QUEUE_DEFAULT_LENGTH) {
    if (default_length != 0) {
      this->pData = (T *) malloc(default_length * sizeof(T));
      this->length = 0;
      this->total_length = default_length;
      this->pFront = pData;
      this->pRear = pFront + sizeof(T);
    } else {
      this->length = 0;
      this->total_length = 0;
      this->pData = NULL;
      this->pFront = NULL;
      this->pRear = NULL;
    }
  }

  ~CircularQueue() {
    free(this->pData);
  }

  void push(T data) {
    if (length == total_length) { //need to enlarge the space
      if (pData != NULL) {
        uint16_t size1 = pRear - pData;
        uint16_t size2 = pFront - pData;
        T *tmp = (T *) realloc(pData, total_length + CIRCULAR_QUEUE_ALLOC_LEN * sizeof(T));
        if (tmp != NULL) {
          pData = tmp;
          pRear = pData + size1;
          pFront = pData + size2;
        }
        if (pRear <= pFront && pRear != pData) {
          tmp = (T *) malloc(pRear - pData);
          memcpy(tmp, pData, pRear - pData);
          memcpy(pData + total_length * sizeof(T), tmp, pRear - pData);
          free(tmp);
          pRear = pFront + length * sizeof(T);
        }
        length++;
        total_length += CIRCULAR_QUEUE_ALLOC_LEN;
        *pRear = data;
        pRear += sizeof(T);
      } else {
        this->pData = (T *) malloc(CIRCULAR_QUEUE_DEFAULT_LENGTH * sizeof(T));
        length++;
        total_length = CIRCULAR_QUEUE_DEFAULT_LENGTH;
        pFront = pData;
        *pFront = data;
        pRear = pData + sizeof(T);
      }
    } else {
      *pRear = data;
      if (pRear - pData == total_length * sizeof(T))pRear = pData;
      else pRear += sizeof(T);
      length++;
    }
  }

  void pop() {
    if (length != 0) {
      if (pFront - pData < total_length * sizeof(T))pFront += sizeof(T);
      else pFront = pData;
      length--;
    }
  }

  T &front() {
    return *pFront;
  }

  bool isEmpty() {
    if (length == 0)return true;
    else return false;
  }

  bool isFull() {
    if (length == total_length)return true;
    else return false;
  }
};


#endif //CIRCULAR_QUEUE_HPP
