#include "item.hpp"

Item::Item(std::string name)
{
  this->name = name;
}

Item::~Item()
{
}

bool Item::Render(cairo_t*)
{
  return true;
}
