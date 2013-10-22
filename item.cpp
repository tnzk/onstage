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
  this->scale = 4;
  this->x = 0;
  this->y = 0;
}

Item::~Item()
{
  rsvg_handle_free(this->rsvg);
}

bool Item::Render(cairo_t* cairo)
{
  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                                        this->width * this->scale,
                                                        this->height *  this->scale);
  cairo_t* cairoInternal = cairo_create(surface);

  cairo_scale(cairoInternal, this->scale, this->scale);
  rsvg_handle_render_cairo(this->rsvg, cairoInternal);

  cairo_set_source_surface(cairo, surface, this->x, this->y);
  cairo_paint(cairo);

  cairo_destroy(cairoInternal);
  cairo_surface_destroy(surface);

  return true;
}
