#include "arm.hpp"
#include <math.h>
#include <iostream>

Arm::Arm(Symbol* symbol, std::string direction)
{
  this->symbol = symbol;
  this->hand = this->symbol->GetRenderableById("hand");
  this->baseHandPosition.first = this->hand->x;
  this->baseHandPosition.second = this->hand->y;
  this->direction = direction;
}

bool Arm::SetPosition(double angle, double distance)
{
  double x = this->baseHandPosition.first + distance * cos(angle);
  double y = this->baseHandPosition.second + distance * sin(angle);
  this->hand->x = x;
  this->hand->y = y;

  IRenderable* shoulder = this->symbol->GetRenderableById("shoulder");

  double upperArmLength = 60;
  double theta = atan2(this->hand->y - shoulder->y, this->hand->x - shoulder->x) - (this->direction == "left" ? 0.3 : -0.3);


  // For the left arm.
  if (this->direction == "left") {
    if (theta >= 0 && theta < M_PI /  1.9) theta = M_PI /  1.9;
    if (theta <  0 && theta > M_PI / -1.1) theta = M_PI / -1.1;
  }
  
  // For right arm.
  if (this->direction == "right") {
    if (theta < M_PI / -2.9) theta = M_PI / -2.9;
    if (theta > M_PI /  2.3) theta = M_PI /  2.3; 
  }

  IRenderable* elbow = this->symbol->GetRenderableById("elbow");
  elbow->x = upperArmLength * cos(theta) + shoulder->x;
  elbow->y = upperArmLength * sin(theta) + shoulder->y;
  // std::cout << "elbow = {" << elbow->x << ", " << elbow->y << "}" << std::endl;

  double dx = this->hand->x - elbow->x;
  double dy = this->hand->y - elbow->y;
  double distanceLowerArm = sqrt(dx * dx + dy * dy);

  double lowerArmLength = upperArmLength * 0.7;
  if (distanceLowerArm > lowerArmLength) {
    double elbowTheta = atan2(this->hand->y - elbow->y, this->hand->x - elbow->x);
    this->hand->x = lowerArmLength * cos(elbowTheta) + elbow->x;
    this->hand->y = lowerArmLength * sin(elbowTheta) + elbow->y;
  }
  return true;
}

