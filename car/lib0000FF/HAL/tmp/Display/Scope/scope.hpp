#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "oled.hpp"
#include "vector"

class Scope {
private:
  OLED *screen;
  uint16_t x;
  std::vector<float(*)(float)> funcList;
  std::vector<float*> sourceList;
  std::vector<float> funcScaleList;
  std::vector<float> srcScaleList;
  std::vector<float> funcBiasList;
  std::vector<float> srcBiasList;
  std::vector<std::vector<float>> funcPoints;
  std::vector<std::vector<float>> srcPoints;
  void drawPoint();
  void drawAxis();
  bool isGridOn;
  uint8_t mode;
public:
  Scope();
  ~Scope();
  void init(OLED *screen,uint8_t mode = 0);
  uint8_t addFunc(float(*pFunction)(float),float scale = 1,float bias = 0);
  void rmFunc(uint8_t index);
  uint8_t addSource(float *source,float scale = 1,float bias = 0);
  void rmSource(uint8_t index);
  void update();
  void setMode(uint8_t mode);
};

#endif //SCOPE_HPP
