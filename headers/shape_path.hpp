#ifndef SHAPE_PATH_HEADER
#define SHAPE_PATH_HEADER

#include "renderable.hpp"
#include <cairo.h>
#include <tuple>
#include <vector>
#include <string>

class ShapePath : public IRenderable
{
public:
  ShapePath(std::string);
  virtual cairo_surface_t* Render(double scale);
  virtual void Sync(int) {};
  virtual int GetCurrentFrame() {};
  void SetCommand(std::string);
private:
  void ParseCommandString(std::string);
  enum class Command { MOVE, LINE, ARC, CURVE,
                       MOVE_RELATIVE, LINE_RELATIVE,
                       FILL, STROKE,
                       FILL_COLOR, STROKE_COLOR, STROKE_WIDTH};
  std::vector<std::tuple<ShapePath::Command, double, double, double, double, double>> commands;
};
#endif
