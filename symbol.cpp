#include "symbol.hpp"
#include "shape_circle.hpp"
#include "shape_path.hpp"
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
  this->centerX = 0;
  this->centerY = 0;
  this->angle = 0;
  this->scale = 1;
  this->isVisible = true;

  std::stringstream ss;
  ss << "symbols/" << this->name; // TODO: Do not assume the directory always exists
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
  
  this->width = obj["width"].is<double>() ? obj["width"].get<double>() : 0;
  this->height = obj["height"].is<double>() ? obj["height"].get<double>() : 0;
  this->centerX = obj["center-x"].is<double>() ? obj["center-x"].get<double>() : 0;
  this->centerY = obj["center-y"].is<double>() ? obj["center-y"].get<double>() : 0;
  this->angle = obj["angle"].is<double>() ? obj["angle"].get<double>() : 0;
  this->debug = obj["debug"].is<bool>() ? obj["debug"].get<bool>() : 0;

  picojson::array& primitives = obj["primitives"].get<picojson::array>();
  for (auto& element : primitives) {
    picojson::object& primitive = element.get<picojson::object>();
    double requireWidth = 0;
    double requireHeight = 0;
    IRenderable* renderable = NULL;

    std::string primitiveType = primitive["type"].get<std::string>();
    if (primitiveType == "circle") {
      double radius = primitive["radius"].get<double>();
      ShapeCircle* circle = new ShapeCircle(radius);
      renderable = circle;
      renderable->className = "foobar"; // TODO: classify somehow
    }
    if (primitiveType == "path") {
      std::string command = primitive["command"].get<std::string>();
      ShapePath* shape = new ShapePath(command);
      renderable = shape;
      renderable->className = "foobar"; // TODO: classify somehow
    }
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
    renderable->angle = primitive["angle"].is<double>() ? primitive["angle"].get<double>() : 0;
    // Overwrite center position only if specified by primitive-specifier.
    if (primitive["center-x"].is<double>()) renderable->centerX = primitive["center-x"].get<double>();
    if (primitive["center-y"].is<double>()) renderable->centerY = primitive["center-y"].get<double>();
    renderable->isVisible = primitive["visibility"].is<bool>() ? primitive["visibility"].get<bool>() : true;
    renderable->debug = primitive["debug"].is<bool>() ? primitive["debug"].get<bool>() : false;
    if (primitive["width"].is<double>()) {
      double widthByCaller = primitive["width"].get<double>();
      if (renderable->width < widthByCaller) renderable->width = widthByCaller;
    }
    if (primitive["height"].is<double>()) {
      double heightByCaller = primitive["height"].get<double>();
      if (renderable->height < heightByCaller) renderable->height = heightByCaller;
    }

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

  for (IRenderable* renderable : this->layers) {
    if (renderable->isVisible) {
      cairo_surface_t* subsurface = renderable->Render(rscale);
      cairo_translate(cairo, renderable->x * rscale, renderable->y * rscale);
      cairo_rotate(cairo, renderable->angle);
      cairo_translate(cairo, -renderable->centerX * rscale, -renderable->centerY * rscale);
      cairo_set_source_surface(cairo, subsurface, 0, 0);
      cairo_paint(cairo);
      cairo_surface_destroy(subsurface);
      cairo_identity_matrix(cairo);
    }
  }

  if (this->debug) {
    // Draw a bounding box
    cairo_set_source_rgba(cairo, 0.18, 1, 0.18, 0.5);
    cairo_rectangle(cairo, 0, 0, this->width * rscale, this->height * rscale);
    cairo_stroke(cairo);
    // Draw center point
    cairo_set_source_rgba(cairo, 0.18, 1, 0.18, 0.8);
    cairo_arc(cairo, this->centerX, this->centerY, 2, 0, M_PI * 2); 
    cairo_fill(cairo);
  }

  cairo_destroy(cairo);
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

IRenderable* Symbol::GetRenderableById(std::string instanceId)
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

void Symbol::AddRenderable(IRenderable* renderable)
{
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
