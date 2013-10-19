#ifndef ITEM_HEADER

#define ITEM_HEADER

#include <cairo.h>
#include <string>
#include "actable.hpp"

class Item : public IActable
{
public:
  Item();
  ~Item();
};

#endif
