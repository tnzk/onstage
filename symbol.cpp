#include "symbol.hpp"
#include "image_svg.hpp"
#include "renderable.hpp"
#include "picojson.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

Symbol::Symbol(std::string name)
{
  this->name = name;
  this->className = name; // the class name decided here will be overwritten by symbol-specifier if this is nested symbol.
  this->instanceId = this->className; // be likely overwritten
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
  for (auto& element : primitives) {
    picojson::object& primitive = element.get<picojson::object>();
    double requireWidth = 0;
    double requireHeight = 0;
    IRenderable* renderable = NULL;

    std::string primitiveType = primitive["type"].get<std::string>();
    if (primitiveType == "svg") {
      std::string path = primitive["path"].get<std::string>();
      ImageSvg* svg = new ImageSvg(path);
      renderable = svg;
      renderable->className = path;
    }
    if (primitiveType == "symbol") {
      std::string path = primitive["path"].get<std::string>();
      Symbol* symbol = new Symbol(path);
      renderable = symbol;
      renderable->className = path;
    }
    // TODO: make sure no instance id is duplicate.
    renderable->instanceId = primitive["id"].is<std::string>() ? primitive["id"].get<std::string>() : renderable->className;
    renderable->x = primitive["x"].is<double>() ? primitive["x"].get<double>() : 0;
    renderable->y = primitive["y"].is<double>() ? primitive["y"].get<double>() : 0;
    renderable->isVisible = primitive["visibility"].is<bool>() ? primitive["visibility"].get<bool>() : true;

    if (primitive["meta"].is<picojson::object>()) {
      picojson::object metadata = primitive["meta"].get<picojson::object>();
      for (auto& element : metadata) {
        // TODO: Make sure if using #to_str here is appropriate
        renderable->meta.insert(std::make_pair(element.first, element.second.to_str()));
      }
    }

    layers.push_back(renderable);

    requireWidth = renderable->x + renderable->width;
    requireHeight = renderable->y + renderable->height;
    
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

  if (this->debug) {
    cairo_set_source_rgba(cairo, 0.1, 0.1, 0.18, 0.3);
    cairo_rectangle(cairo, 0, 0, this->width * rscale, this->height * rscale);
    cairo_fill(cairo);
  }

  for (IRenderable* element : this->layers) {
    IRenderable* svg = element;
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

IRenderable* Symbol::GetRenderable(std::string instanceId)
{
  std::list<IRenderable*>::iterator it;
  it = std::find_if(this->layers.begin(), this->layers.end(), [instanceId](IRenderable* renderable) { return renderable->instanceId == instanceId; });
  return it != this->layers.end() ? *it : NULL;
}

void Symbol::Sync(int frame)
{
  // std::cout << "Symbol::Sync at " << frame << " for " << this->className << std::endl;
  this->currentFrame = frame;
}

int Symbol::GetCurrentFrame()
{
  return this->currentFrame;
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
