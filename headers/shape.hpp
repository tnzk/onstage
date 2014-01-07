#ifndef SHAPE_HEADER

#define SHAPE_HEADER

#include "renderable.hpp"
#include <cairo.h>

class Shape : public IRenderable
{
public:
  Shape();
  virtual cairo_surface_t* Render(double scale);
};

#endif
