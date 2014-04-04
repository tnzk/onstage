#include "eyes.hpp"
#include <math.h>
#include <iostream>
#include <sstream>

Eyes::Eyes(Symbol* symbol)
{
  this->symbol = symbol;
  if (this->symbol->meta.find("distance") != this->symbol->meta.end()) {
    std::istringstream(symbol->meta["distance"]) >> this->distance;
  } else {
    this->distance = 15;
  }

  this->pupils.first = symbol->GetRenderableById("left-pupil");
  this->pupils.second = symbol->GetRenderableById("right-pupil");
  this->leftBasePosition.first = this->pupils.first->x;
  this->leftBasePosition.second = this->pupils.first->y;
  this->rightBasePosition.first = this->pupils.second->x;
  this->rightBasePosition.second = this->pupils.second->y;
}

bool Eyes::LookAt(double rad, double distance)
{
  double centerX = this->symbol->width / 2.0;
  double centerY = this->symbol->height / 2.0;
  double focusX = centerX + distance * cos(rad);
  double focusY = centerY + distance * sin(rad);
  double leftCenterX  = this->leftBasePosition.first   + this->pupils.first->width  / 2.0;
  double leftCenterY  = this->leftBasePosition.second  + this->pupils.first->height / 2.0;
  double rightCenterX = this->rightBasePosition.first  + this->pupils.second->width  / 2.0;
  double rightCenterY = this->rightBasePosition.second + this->pupils.second->height / 2.0;
  double leftRad  = atan2(focusY - leftCenterY,  focusX - leftCenterX);
  double rightRad = atan2(focusY - rightCenterY, focusX - rightCenterX);
  this->pupils.first->x = this->leftBasePosition.first  + this->distance * cos(leftRad);
  this->pupils.first->y = this->leftBasePosition.second + this->distance * sin(leftRad) * -1;
  this->pupils.second->x = this->rightBasePosition.first  + this->distance * cos(rightRad);
  this->pupils.second->y = this->rightBasePosition.second + this->distance * sin(rightRad) * -1;

  return true;
}
