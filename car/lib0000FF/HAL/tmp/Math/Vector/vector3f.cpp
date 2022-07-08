#include "vector3f.hpp"
#include <math.h>

Vector3f::Vector3f(float x,float y,float z){
  this->x = x;
  this->y = y;
  this->z = z;
}

float Vector3f::norm(){
  return sqrtf(x*x+y*y+z*z);
}

float& Vector3f::operator[](uint8_t index){
  if(index == 0)return x;
  else if(index == 1)return y;
  else return z;
}
