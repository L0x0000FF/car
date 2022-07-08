#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

#include "stdint.h"

class Vector3f {
 public:
  float x;
  float y;
  float z;

  Vector3f(float x = 0,float y = 0,float z = 0);
  float& operator[](uint8_t index);
  float norm();

};

#endif
