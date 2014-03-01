#include "arm.hpp"
#include "shape_path.hpp"
#include <math.h>
#include <iostream>
#include <sstream>

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
  double y = this->baseHandPosition.second + distance * -sin(angle);
  this->hand->x = x;
  this->hand->y = y;

  ShapePath* shoulder = this->symbol->GetElementById<ShapePath*>("shoulder"); 

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

  ShapePath* elbow = this->symbol->GetElementById<ShapePath*>("elbow");
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

  shoulder->SetCommand(this->GetShoulderPathString(shoulder->centerX, shoulder->centerY,
						   elbow->x - shoulder->x, elbow->y - shoulder->y));
  elbow->SetCommand(this->GetElbowPathString(elbow->centerX, elbow->centerY,
					     hand->x - elbow->x, hand->y - elbow->y));
  
  return true;
}

std::string Arm::GetShoulderPathString(double x, double y, double dx, double dy)
{
  std::stringstream ss;
  double theta = atan2(dy, dx);
  double r = 8;
  double px = x - r * cos(theta);
  double py = y - r * sin(theta);
  double qx = x + dx + r * 1.5 * cos(theta);
  double qy = y + dy + r * 1.5 * sin(theta);
  double c1x = px + 2 * r * cos(theta + M_PI / 2);
  double c1y = py + 2 * r * sin(theta + M_PI / 2);
  double c2x = qx + 4 * r * cos(theta + M_PI / 2);
  double c2y = qy + 4 * r * sin(theta + M_PI / 2);
  double d1x = qx + 4 * r * cos(theta - M_PI / 2);
  double d1y = qy + 4 * r * sin(theta - M_PI / 2);
  double d2x = px + 2 * r * cos(theta - M_PI / 2);
  double d2y = py + 2 * r * sin(theta - M_PI / 2);

  ss << " M " << px << ", " << py  
     << " CURVE " << c1x << ", " << c1y << ", " << c2x << ", " << c2y <<", " << qx << ", " << qy
     << " CURVE " << d1x << ", " << d1y << ", " << d2x << ", " << d2y <<", " << px << ", " << py
     << " Z F";
  std::string result = ss.str();
  return result;
}

std::string Arm::GetElbowPathString(double x, double y, double dx, double dy)
{
  std::stringstream ss;
  double theta = atan2(dy, dx);
  double l = sqrt(dx * dx + dy * dy);
  double volume = 100 - l;
  double r = 20;
  double px = x - r * cos(theta);
  double py = y - r * sin(theta);
  double qx = x + dx + r * 0.7 * cos(theta);
  double qy = y + dy + r * 0.7 * sin(theta);
  double c1x = px + 0.5 * volume * cos(theta + M_PI / 2);
  double c1y = py + 0.5 * volume * sin(theta + M_PI / 2);
  double c2x = qx + 0.3 * volume * cos(theta + M_PI / 2);
  double c2y = qy + 0.3 * volume * sin(theta + M_PI / 2);
  double d1x = qx + 0.3 * volume * cos(theta - M_PI / 2);
  double d1y = qy + 0.3 * volume * sin(theta - M_PI / 2);
  double d2x = px + 0.5 * volume * cos(theta - M_PI / 2);
  double d2y = py + 0.5 * volume * sin(theta - M_PI / 2);

  ss << " M " << px << ", " << py  
     << " CURVE " << c1x << ", " << c1y << ", " << c2x << ", " << c2y <<", " << qx << ", " << qy
     << " CURVE " << d1x << ", " << d1y << ", " << d2x << ", " << d2y <<", " << px << ", " << py
     << " Z F";
  std::string result = ss.str();
  return result;
}
