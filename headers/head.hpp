#ifndef HEAD_HEADER
#define HEAD_HEADER

#include "symbol.hpp"

class Head
{
public:
  Head(Symbol*);
  ~Head();
  bool LookAt(double r, double distance);
  bool Eyeblows(double r);
  bool Hand(double left_r,  double left_distance, 
            double right_r, double right_distance);
  bool Speak();
  bool Shut();

private:
  bool isSpeaking;
  Symbol* symbol;
};


#endif
