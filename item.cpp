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
      layers.push_back(svg);
      this->width = svg->width;
      this->height = svg->height;
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
