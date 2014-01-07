#ifndef PRIMITIVE_HEADER

#define PRIMITIVE_HEADER

#include <cairo.h>

class IPrimitive
{
public:
  virtual cairo_surface_t* Render(double scale) = 0;
  double width;
  double height;
};

#endif
