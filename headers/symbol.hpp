#ifndef SYMBOL_HEADER
#define SYMBOL_HEADER

#include <cairo.h>
#include <string>
#include "isymbol.hpp"
#include "camera.hpp"

class Symbol : public ISymbol
{
public:
  Symbol(std::string name);
  ~Symbol();
  virtual std::string GetName();
  virtual cairo_surface_t* Render(double scale);
  virtual void SetScale(double);
  virtual double GetScale();
  virtual void SetPosition(double, double);
  virtual void Move(double, double);
private:
};

#endif
