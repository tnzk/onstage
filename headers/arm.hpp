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
  std::string direction;
  std::pair<double, double> baseHandPosition;
};


#endif
