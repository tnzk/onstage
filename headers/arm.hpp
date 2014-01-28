#ifndef ARM_HEADER
#define ARM_HEADER

#include "symbol.hpp"

class Arm
{
public:
  Arm(Symbol*);
  bool SetPosition(double angle, double distance);
private:
  Symbol* symbol;
  IRenderable* hand;
  std::pair<double, double> baseHandPosition;
};


#endif
