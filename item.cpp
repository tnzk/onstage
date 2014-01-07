#include "item.hpp"
#include "image_svg.hpp"
#include "renderable.hpp"
#include "picojson.h"
#include <sstream>
#include <iostream>
#include <fstream>

Item::Item(std::string name)
{
  this->name = name;
  this->x = 0;
  this->y = 0;
  this->width = 0;
  this->height = 0;

  std::stringstream ss;
  ss << "symbols/" << this->name;
  std::string path = ss.str();

  std::ifstream symbolFile(path);
  if (!symbolFile.is_open()) {
    std::cout << "No such file: " <<  path << std::endl;
    exit(1);
  }

  picojson::value json;
  symbolFile >> json;
  symbolFile.close();
  picojson::object& obj = json.get<picojson::object>();

  std::string type = obj["type"].get<std::string>();
  if (type != "item") {
    std::cout << "Warning: an item is going to be initialize by the symbol whose type is " << type << std::endl;
  }

  picojson::array& primitives = obj["primitives"].get<picojson::array>();
  for (picojson::array::iterator it = primitives.begin(); it != primitives.end(); ++it) {
    picojson::object& primitive = (*it).get<picojson::object>();
    std::string primitiveType = primitive["type"].get<std::string>();
    if (primitiveType == "svg") {
      std::string path = primitive["path"].get<std::string>();
      ImageSvg* svg = new ImageSvg(path);
      svg->x = primitive["x"].get<double>();
      svg->y = primitive["y"].get<double>();
      svg->isVisible = primitive["visibility"].is<bool>() ? primitive["visibility"].get<bool>() : true;
      layers.push_back(svg);
      double requireWidth = svg->x + svg->width;
      double requireHeight = svg->y + svg->height;

      if (this->width < requireWidth) this->width = requireWidth;
      if (this->height < requireHeight) this->height = requireHeight;
    }
  }

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

  for (std::list<IRenderable*>::iterator it = this->layers.begin(); it != this->layers.end(); ++it) {
    IRenderable* svg = *it;
    if (svg->isVisible) {
      cairo_surface_t* subsurface = svg->Render(rscale);
      cairo_set_source_surface(cairo, subsurface, svg->x * rscale, svg->y * rscale);
      cairo_paint(cairo);
      cairo_surface_destroy(subsurface);
    }
  }

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
