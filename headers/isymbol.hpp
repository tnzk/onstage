#ifndef ISYMBOL_HEADER
#define ISYMBOL_HEADER

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
  virtual IRenderable* GetRenderableById(std::string) = 0;
  virtual void AddRenderable(IRenderable*) = 0;
  template<typename T> T GetElementById(std::string id)
  {
    return dynamic_cast<T>(this->GetRenderableById(id));
  };

  std::list<IRenderable*> layers;

protected:
  int id;
  std::string name;
  int innerCount;
};

#endif
