#ifndef ARM_HEADER
#define ARM_HEADER

#include "symbol.hpp"

class Arm
{
public:
  Arm(Symbol*, std::string);
  bool SetPosition(double angle, double distance);
private:
  Symbol* symbol;
  IRenderable* hand;
  IRenderable* sleeve;
  int length = 60;
  std::string direction;
  std::string GetShoulderPathString(double x, double y, double dx, double dy);
  std::string GetElbowPathString(double x, double y, double dx, double dy);
  std::pair<double, double> baseHandPosition;
};


#endif
