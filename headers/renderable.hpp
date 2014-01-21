#ifndef RENDERABLE_HEADER
#define RENDERABLE_HEADER

#include <cairo.h>
#include <string>
#include <map>

class IRenderable
{
public:
  virtual cairo_surface_t* Render(double scale) = 0;
  virtual void Sync(int) = 0;
  virtual int GetCurrentFrame() = 0;

  double width;
  double height;
  double x;
  double y;
  double scale;
  double angle;
  double centerX;
  double centerY;
  bool isVisible;
  bool debug = false;
  std::string instanceId;
  std::string className;
  std::map<std::string, std::string> meta;
protected:
  int currentFrame;
};

#endif
