#ifndef SHAPE_PATH_HEADER
#define SHAPE_PATH_HEADER

#include "renderable.hpp"
#include <cairo.h>
#include <tuple>
#include <string>

class ShapePath : public IRenderable
{
public:
  ShapePath(std::string);
  virtual cairo_surface_t* Render(double scale);
  virtual void Sync(int) {};
  virtual int GetCurrentFrame() {};
private:
  std::string command;
};

#endif
