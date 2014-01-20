#include "eyes.hpp"
#include <math.h>
#include <iostream>

Eyes::Eyes(Symbol* symbol)
{
  this->symbol = symbol;
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
  this->pupils.first->x = this->leftBasePosition.first  + 15 * cos(leftRad);
  this->pupils.first->y = this->leftBasePosition.second + 15 * sin(leftRad);
  this->pupils.second->x = this->rightBasePosition.first  + 15 * cos(rightRad);
  this->pupils.second->y = this->rightBasePosition.second + 15 * sin(rightRad);

  return true;
}
