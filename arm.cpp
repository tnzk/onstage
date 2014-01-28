#include "arm.hpp"
#include <math.h>
#include <iostream>

Arm::Arm(Symbol* symbol)
{
  this->symbol = symbol;
  this->hand = this->symbol->GetRenderableById("hand");
  this->baseHandPosition.first = this->hand->x;
  this->baseHandPosition.second = this->hand->y;
}

bool Arm::SetPosition(double angle, double distance)
{
  double x = this->baseHandPosition.first + distance * cos(angle);
  double y = this->baseHandPosition.second + distance * sin(angle);
  this->hand->x = x;
  this->hand->y = y;
  return true;
}

