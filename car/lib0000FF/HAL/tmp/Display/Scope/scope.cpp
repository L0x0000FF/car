#include "scope.hpp"
#include "algorithm"
#include "math.h"

Scope::Scope() {
  this->x = 0;
  this->mode = 0;
  this->isGridOn = false;
}

Scope::~Scope() {

}

void Scope::init(OLED *screen, uint8_t mode) {
  this->screen = screen;
  this->mode = mode;
}

uint8_t Scope::addFunc(float (*f)(float), float factor, float bias) {
  this->funcList.push_back(f);
  std::vector<float> tmp;
  this->funcPoints.push_back(tmp);
  for (uint8_t i = 0; i < this->funcList.size(); i++)this->funcPoints[i].clear();
  this->x = 0;
  this->funcScaleList.push_back(factor);
  this->funcBiasList.push_back(bias);
  return this->funcList.size();
}

void Scope::rmFunc(uint8_t index) {
  this->funcList.erase(this->funcList.begin() + index);
  this->funcScaleList.erase(this->funcScaleList.begin() + index);
  this->funcBiasList.erase(this->funcBiasList.begin() + index);
}

uint8_t Scope::addSource(float *source, float factor, float bias) {
  this->sourceList.push_back(source);
  std::vector<float> tmp;
  this->srcPoints.push_back(tmp);
  for (uint8_t i = 0; i < this->funcList.size(); i++)this->srcPoints[i].clear();
  this->x = 0;
  this->srcScaleList.push_back(factor);
  this->srcBiasList.push_back(bias);
  return this->sourceList.size();
}

void Scope::rmSource(uint8_t index) {
  this->sourceList.erase(this->sourceList.begin() + index);
  this->srcScaleList.erase(this->srcScaleList.begin() + index);
  this->srcBiasList.erase(this->srcBiasList.begin() + index);
}

void Scope::update() {
  if (this->funcList.size() > 0 || this->srcPoints.size()) {
    for (uint8_t i = 0; i < this->funcList.size(); i++) {
      this->funcPoints[i].push_back((this->funcList[i](x) + this->funcBiasList[i]) * this->funcScaleList[i]);
    }
    for (uint8_t i = 0; i < this->sourceList.size(); i++) {
      this->srcPoints[i].push_back((*(this->sourceList[i]) + this->srcBiasList[i]) * this->srcScaleList[i]);
    }
    this->screen->GRAMFill(0);
    this->drawAxis();
    this->drawPoint();
    this->x++;
    if (this->x > 127) {
      for (uint8_t i = 0; i < this->funcList.size(); i++)this->funcPoints[i].erase(this->funcPoints[i].begin());
      for (uint8_t i = 0; i < this->sourceList.size(); i++)this->srcPoints[i].erase(this->srcPoints[i].begin());
    }
  }
}

void Scope::drawPoint() {
  if (mode == 0) {
    for (uint8_t i = 0; i < this->funcPoints.size(); i++) {
      for (uint8_t j = 0; j < this->funcPoints[0].size(); j++) {
        this->screen->GRAMDrawPoint(j, 32 - this->funcPoints[i][j]);
      }
    }
    for (uint8_t i = 0; i < this->srcPoints.size(); i++) {
      for (uint8_t j = 0; j < this->srcPoints[0].size(); j++) {
        this->screen->GRAMDrawPoint(j, 32 - this->srcPoints[i][j]);
      }
    }
  } else {
    for (uint8_t i = 0; i < this->funcPoints.size(); i++) {
      for (uint8_t j = 0; j < this->funcPoints[0].size(); j++) {
        this->screen->GRAMDrawPoint(j, 64 - this->funcPoints[i][j]);
      }
    }
    for (uint8_t i = 0; i < this->srcPoints.size(); i++) {
      for (uint8_t j = 0; j < this->srcPoints[0].size(); j++) {
        this->screen->GRAMDrawPoint(j, 64 - this->srcPoints[i][j]);
      }
    }
  }
}

void Scope::drawAxis() {
  //x axis
  this->screen->GRAMDrawLine(0, 0, 0, 64);
  this->screen->GRAMDrawPoint(1, 1);
  //y axis
  if (mode == 0) {
    this->screen->GRAMDrawLine(0, 32, 127, 32);
    this->screen->GRAMDrawPoint(126, 31);
    this->screen->GRAMDrawPoint(126, 33);
  } else {
    this->screen->GRAMDrawLine(0, 63, 127, 63);
    this->screen->GRAMDrawPoint(126, 62);
    this->screen->GRAMDrawPoint(126, 62);
  }
}

void Scope::setMode(uint8_t mode) {
  Scope::mode = mode;
}

