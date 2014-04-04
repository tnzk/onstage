#ifndef EYES_HEADER
#define EYES_HEADER

#include <map>
#include "symbol.hpp"

class Eyes
{
public:
  Eyes(Symbol*);
  ~Eyes();
  bool LookAt(double rad, double distance);
  void Sync(int);
private:
  bool isBlinking;
  Symbol* symbol;
  double distance;
  std::pair<IRenderable*, IRenderable*> pupils;
  std::pair<double, double> leftBasePosition;
  std::pair<double, double> rightBasePosition;
};


#endif
