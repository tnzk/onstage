#ifndef PRIMITIVE_HEADER

#define PRIMITIVE_HEADER

#include <cairo.h>

class IRenderable
{
public:
  virtual cairo_surface_t* Render(double scale) = 0;
  double width;
  double height;
  double x;
  double y;
  double scale;
  bool isVisible;
};

#endif
