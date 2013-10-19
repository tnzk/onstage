#include <cairo.h>

class IActable
{
public:
  virtual bool Render(cairo_t*) = 0;
protected:
  int id;
  int x;
  int y;
  int innerCount;  
};
