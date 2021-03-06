#include "arm.hpp"
#include "shape_path.hpp"
#include <math.h>
#include <iostream>
#include <sstream>

Arm::Arm(Symbol* symbol, std::string direction)
{
  this->symbol = symbol;
  // TODO: Support the actor that doesnt have hand or sleeve.
  this->hand = this->symbol->GetRenderableById("hand");
  this->sleeve = this->symbol->GetRenderableById("sleeve");
  this->baseHandPosition.first = this->hand->x;
  this->baseHandPosition.second = this->hand->y;
  this->direction = direction;
  if (symbol->meta.find("length") == symbol->meta.end()) {
    this->length = 60;
  } else {
    this->length = std::stoi(symbol->meta["length"]);
  }
}

bool Arm::SetPosition(double angle, double distance)
{
  bool isLeft = this->direction == "left";
  double x = this->baseHandPosition.first + distance * cos(angle);
  double y = this->baseHandPosition.second + distance * -sin(angle);
  this->hand->x = x;
  this->hand->y = y;

  ShapePath* shoulder = this->symbol->GetElementById<ShapePath*>("shoulder"); 

  double upperArmLength = this->length;
  double theta = atan2(this->hand->y - shoulder->y, this->hand->x - shoulder->x) - (isLeft ? 0.3 : -0.3);

  // Normalize the reaching point.
  if (isLeft) {
    if (theta >= 0 && theta < M_PI /  1.9) theta = M_PI /  1.9;
    if (theta <  0 && theta > M_PI / -1.1) theta = M_PI / -1.1;
  } else {
    if (theta < M_PI / -2.9) theta = M_PI / -2.9;
    if (theta > M_PI /  2.3) theta = M_PI /  2.3; 
  }

  ShapePath* elbow = this->symbol->GetElementById<ShapePath*>("elbow");
  elbow->x = upperArmLength * cos(theta) + shoulder->x;
  elbow->y = upperArmLength * sin(theta) + shoulder->y;

  double dx = this->hand->x - elbow->x;
  double dy = this->hand->y - elbow->y;
  double distanceLowerArm = sqrt(dx * dx + dy * dy);

  double lowerArmLength = upperArmLength * 0.7;
  if (distanceLowerArm > lowerArmLength) {
    double elbowTheta = atan2(this->hand->y - elbow->y, this->hand->x - elbow->x);
    this->hand->x = lowerArmLength * cos(elbowTheta) + elbow->x;
    this->hand->y = lowerArmLength * sin(elbowTheta) + elbow->y;
    this->hand->angle = elbowTheta;
  }

  shoulder->SetCommand(this->GetShoulderPathString(shoulder->centerX, shoulder->centerY,
						   elbow->x - shoulder->x, elbow->y - shoulder->y));
  elbow->SetCommand(this->GetElbowPathString(elbow->centerX, elbow->centerY,
					     hand->x - elbow->x, hand->y - elbow->y));

  if (sleeve) {
    sleeve->x = shoulder->x;
    sleeve->y = shoulder->y;
    sleeve->angle = theta + (isLeft ? 0.1 : -0.1);
  }

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
  double c2x = qx + 2.5 * r * cos(theta + M_PI / 2);
  double c2y = qy + 2.5 * r * sin(theta + M_PI / 2);
  double d1x = qx + 2.5 * r * cos(theta - M_PI / 2);
  double d1y = qy + 2.5 * r * sin(theta - M_PI / 2);
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
  double volume = 70 - l;
  double r = 20;
  double px = x - 0.1 * cos(theta);
  double py = y - 0.1 * sin(theta);
  double qx = x + dx + 0.1 * cos(theta);
  double qy = y + dy + 0.1 * sin(theta);
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
