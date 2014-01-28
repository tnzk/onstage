#ifndef SHAPE_CIRCLE_HEADER
#define SHAPE_CIRCLE_HEADER

#include "renderable.hpp"
#include <cairo.h>
#include <tuple>

class ShapeCircle : public IRenderable
{
public:
  ShapeCircle(double radius);
  virtual cairo_surface_t* Render(double scale);
  virtual void Sync(int) {};
  virtual int GetCurrentFrame() {};
private:
  double radius;
  double strokeWidth;
  std::tuple<double, double, double> fillColor;
  std::tuple<double, double, double> strokeColor;
};

#endif
