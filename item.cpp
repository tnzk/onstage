#include "item.hpp"
#include <sstream>
#include <iostream>

Item::Item(std::string name)
{
  this->name = name;
  std::stringstream ss;
  ss << "svgs/" << this->name;

  this->rsvg = rsvg_handle_new_from_file(ss.str().c_str(), NULL);

  RsvgDimensionData dimention;
  rsvg_handle_get_dimensions(rsvg, &dimention);
  this->width  = dimention.width;
  this->height = dimention.height;
}

Item::~Item()
{
  rsvg_handle_free(this->rsvg);
}

bool Item::Render(cairo_t* cairo)
{
  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, this->width, this->height);
  cairo_t* cairoInternal = cairo_create(surface);

  rsvg_handle_render_cairo(this->rsvg, cairoInternal);

  cairo_set_source_surface(cairo, surface, 0, 0);
  cairo_paint(cairo);

  return true;
}
