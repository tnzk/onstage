#ifndef ACTABLE_HEADER

#define ACTABLE_HEADER

#include <string>
#include <cairo.h>
#include "camera.hpp"

class IActable
{
public:
  virtual std::string GetName() = 0;
  virtual void SetScale(double) = 0;
  virtual double GetScale() = 0;
  virtual bool Render(cairo_t*, Camera*) = 0;
protected:
  int id;
  std::string name;
  int innerCount;

  double x;
  double y;
  int width;
  int height;
  double scale;
};

#endif
