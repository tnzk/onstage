#include "item.hpp"
#include <sstream>
#include <iostream>

Item::Item(std::string name)
{
  this->name = name;
  std::stringstream ss;
  ss << "svgs/" << this->name;
  std::cout << "constructor of Item" << std::endl;
  rsvg = rsvg_handle_new_from_file(ss.str().c_str(), NULL);
}

Item::~Item()
{
  std::cout << "destructor of Item" << std::endl;
  rsvg_handle_free(this->rsvg);
}

bool Item::Render(cairo_t* cairo)
{
  rsvg_handle_render_cairo(this->rsvg, cairo);
  return true;
}
