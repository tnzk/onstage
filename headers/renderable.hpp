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

  double width = 0;
  double height = 0;
  double x = 0;
  double y = 0;
  double scale = 1;
  double angle = 0;
  double centerX = 0;
  double centerY = 0;
  bool isVisible = true;
  bool debug = false;
  std::string instanceId;
  std::string className;
  std::map<std::string, std::string> meta;
protected:
  int currentFrame;
};

#endif
