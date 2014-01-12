#include "symbol.hpp"
#include "image_svg.hpp"
#include "renderable.hpp"
#include "picojson.h"
#include <sstream>
#include <iostream>
#include <fstream>

Symbol::Symbol(std::string name)
{
  this->name = name;
  this->x = 0;
  this->y = 0;
  this->width = 0;
  this->height = 0;
  this->scale = 1;
  this->isVisible = true;

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

  picojson::array& primitives = obj["primitives"].get<picojson::array>();
  for (picojson::array::iterator it = primitives.begin(); it != primitives.end(); ++it) {
    picojson::object& primitive = (*it).get<picojson::object>();
    double requireWidth = 0;
    double requireHeight = 0;

    std::string primitiveType = primitive["type"].get<std::string>();
    if (primitiveType == "svg") {
      std::string path = primitive["path"].get<std::string>();
      ImageSvg* svg = new ImageSvg(path);
      svg->x = primitive["x"].is<double>() ? primitive["x"].get<double>() : 0;
      svg->y = primitive["y"].is<double>() ? primitive["y"].get<double>() : 0;
      svg->isVisible = primitive["visibility"].is<bool>() ? primitive["visibility"].get<bool>() : true;
      layers.push_back(svg);
      requireWidth = svg->x + svg->width;
      requireHeight = svg->y + svg->height;
    }
    if (primitiveType == "symbol") {
      std::string path = primitive["path"].get<std::string>();
      Symbol* symbol = new Symbol(path);
      symbol->x = primitive["x"].is<double>() ? primitive["x"].get<double>() : 0;
      symbol->y = primitive["y"].is<double>() ? primitive["y"].get<double>() : 0;
      symbol->isVisible = primitive["visibility"].is<bool>() ? primitive["visibility"].get<bool>() : true;
      layers.push_back(symbol);
      requireWidth = symbol->x + symbol->width;
      requireHeight = symbol->y + symbol->height;
    }
    if (this->width < requireWidth) this->width = requireWidth;
    if (this->height < requireHeight) this->height = requireHeight;
  }

}

Symbol::~Symbol()
{
}

cairo_surface_t* Symbol::Render(double scale)
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

void Symbol::SetScale(double scale) { this->scale = scale;}
double Symbol::GetScale() { return this->scale;}
std::string Symbol::GetName() { return this->name; }
void Symbol::SetPosition(double x, double y)
{
  this->x = x;
  this->y = y;
}
void Symbol::Move(double dx, double dy)
{
  this->SetPosition(this->x + dx, this->y + dy);
}



/*
void Symbol::SavePng(std::string name)
{
  cairo_surface_t* surface = this->Render(1);
  std::stringstream filename;
  filename << name;
  cairo_surface_write_to_png(surface, filename.str().c_str());
}
*/
