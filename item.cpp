#include "item.hpp"
#include "image_svg.hpp"
#include "renderable.hpp"
#include <sstream>
#include <iostream>

Item::Item(std::string name)
{
  this->name = name;
  this->x = 0;
  this->y = 0;

  ImageSvg* svg = new ImageSvg(this->name);
  layers.push_back(svg);
  this->width = svg->width;
  this->height = svg->height;
}

Item::~Item()
{
}

cairo_surface_t* Item::Render(double scale)
{
  double rscale = this->scale * scale;
  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                                        this->width * rscale,
                                                        this->height * rscale);
  cairo_t* cairo = cairo_create(surface);

  IRenderable* svg = this->layers.front();
  cairo_surface_t* subsurface = svg->Render(rscale);
  cairo_set_source_surface(cairo, subsurface, 0, 0);
  cairo_paint(cairo);
  cairo_surface_destroy(subsurface);
 
  return surface;
}

void Item::SetScale(double scale) { this->scale = scale;}
double Item::GetScale() { return this->scale;}
std::string Item::GetName() { return this->name; }
void Item::SetPosition(double x, double y)
{
  this->x = x;
  this->y = y;
}
void Item::Move(double dx, double dy)
{
  this->SetPosition(this->x + dx, this->y + dy);
}
