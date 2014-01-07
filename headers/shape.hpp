#ifndef SHAPE_HEADER

#define SHAPE_HEADER

#include "primitive.hpp"
#include <cairo.h>

class Shape : public IPrimitive
{
public:
  Shape();
  virtual cairo_surface_t* Render(double scale);
};

#endif
