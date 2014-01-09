#ifndef ACTABLE_HEADER

#define ACTABLE_HEADER

#include <list>
#include <string>
#include <cairo.h>
#include "renderable.hpp"
#include "camera.hpp"

class ISymbol : public IRenderable
{
public:
  virtual std::string GetName() = 0;
  virtual void SetScale(double) = 0;
  virtual void SetPosition(double, double) = 0;
  virtual void Move(double, double) = 0;
  virtual double GetScale() = 0;

  std::list<IRenderable*> layers;

protected:
  int id;
  std::string name;
  int innerCount;
};

#endif
