#ifndef ITEM_HEADER

#define ITEM_HEADER

#include <cairo.h>
#include <string>
#include "actable.hpp"
#include "camera.hpp"

class Item : public IActable
{
public:
  Item(std::string name);
  ~Item();
  virtual std::string GetName();
  virtual cairo_surface_t* Render(double scale);
  virtual void SetScale(double);
  virtual double GetScale();
  virtual void SetPosition(double, double);
  virtual void Move(double, double);
private:
};

#endif
