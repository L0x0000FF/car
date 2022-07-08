#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
  float x;
  float y;
  float z;
}Vector3f;

typedef struct{
  int x;
  int y;
  int z;
}Vector3i;

typedef struct{
  float w;
  float x;
  float y;
  float z;
}Vector4f;

typedef struct{
  int w;
  int x;
  int y;
  int z;
}Vector4i;

#ifdef __cplusplus
}
#endif

#endif //STRUCTS_H
