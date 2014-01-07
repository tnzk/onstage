#include "item.hpp"
#include "image_svg.hpp"
#include "primitive.hpp"
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

bool Item::Render(cairo_t* cairo, Camera* camera)
{
  double rscale = this->scale * camera->GetZoom();

  double rx;
  double ry;
  IPrimitive* svg = this->layers.front();
  cairo_surface_t* subsurface = svg->Render(rscale);
  camera->Translate(this->x, this->y, rx, ry);
  cairo_set_source_surface(cairo, subsurface, rx, ry);
  cairo_paint(cairo);
  cairo_surface_destroy(subsurface);
 
  return true;
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
