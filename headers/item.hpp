#ifndef ITEM_HEADER

#define ITEM_HEADER

#include <librsvg/rsvg.h>
#include <librsvg/rsvg-cairo.h>
#include <cairo.h>
#include <string>
#include "actable.hpp"

class Item : public IActable
{
public:
  Item(std::string name);
  ~Item();
  virtual bool Render(cairo_t*);
  virtual void SetScale(double) ;
  virtual double GetScale();
private:
  RsvgHandle* rsvg;
  std::string name;
};

#endif
