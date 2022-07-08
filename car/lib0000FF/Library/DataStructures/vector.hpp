#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_ALLOC_LEN 3

template<class T>
class Vector {
private:
  T *pData;
  size_t length;
  size_t total_length;

public:
  Vector(const size_t default_length = 0) {
    if (default_length == 0) {
      pData = NULL;
      length = total_length = 0;
    } else {
      pData = (T *) malloc(default_length * sizeof(T));
      length = 0;
      if (pData == NULL)
        total_length = 0;
      else
        total_length = default_length;
    }
  }

  Vector(Vector &v) {
    this->length = v.length;
    this->total_length = v.total_length;
    if (v.pData != NULL) {
      this->pData = (T *) malloc(total_length * sizeof(T));
      memcpy(this->pData,v.pData,total_length*sizeof(T));
    } else this->pData = v.pData;
  }

  ~Vector() { free(pData); }

  size_t getLength() { return length; }

  size_t getTotalLength() { return total_length; }

  void push_back(const T &member) {
    if (length <= total_length - 1) {
      pData[length - 1] = member;
      length++;
    } else {
      total_length += VECTOR_ALLOC_LEN;
      T *tmp = (T *) realloc(pData, total_length);
      if (tmp != NULL) {
        pData = tmp;
        length++;
      }
    }
  }

  void pop_back() {
    if (length != 0) length--;
  }

  T &operator[](const int index) {
    if (index >= 0) {
      T &result = pData[length - 1];
      return result;
    } else {
      T &result = pData[length + index];
      return result;
    }
  }
};

#endif  // VECTOR_H
