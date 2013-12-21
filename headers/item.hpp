#ifndef ITEM_HEADER

#define ITEM_HEADER

#include <librsvg/rsvg.h>
#include <librsvg/rsvg-cairo.h>
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
  virtual bool Render(cairo_t*, Camera*);
  virtual void SetScale(double);
  virtual double GetScale();
  virtual void SetPosition(double, double);
  virtual void Move(double, double);
private:
  RsvgHandle* rsvg;
};

#endif
