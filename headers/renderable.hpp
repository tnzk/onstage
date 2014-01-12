#ifndef RENDERABLE_HEADER
#define RENDERABLE_HEADER

#include <cairo.h>
#include <string>

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
  std::string instanceId;
  std::string className;
};

#endif
