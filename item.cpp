#include "item.hpp"
#include <sstream>
#include <iostream>

Item::Item(std::string name)
{
  this->name = name;
  rsvg_init();
  rsvg_term();
}

Item::~Item()
{
}

bool Item::Render(cairo_t* cairo)
{
  std::stringstream ss;
  ss << "svgs/" << this->name;

  rsvg_init();
  rsvg = rsvg_handle_new_from_file(ss.str().c_str(), NULL);
  rsvg_handle_render_cairo(this->rsvg, cairo);
  rsvg_handle_free(this->rsvg);
  rsvg_term();

  return true;
}
