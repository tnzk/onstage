#include "shape_path.hpp"
#include <math.h>
#include <sstream>

ShapePath::ShapePath(std::string command)
{
  this->command = command;
  this->width = 200;
  this->height = 200;
}

cairo_surface_t* ShapePath::Render(double scale)
{
  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                                        this->width * scale,
                                                        this->height * scale);
  cairo_t* cairo = cairo_create(surface);
  cairo_scale(cairo, scale, scale);

  if (this->debug) {
    // Draw a bounding box
    cairo_set_source_rgba(cairo, 1.0, 0, 0.9, 0.5);
    cairo_rectangle(cairo, 0, 0, this->width * scale, this->height * scale);
    cairo_stroke(cairo);
    // Draw center point
    cairo_set_source_rgba(cairo, 1.0, 0, 0.9, 0.8);
    cairo_arc(cairo, this->centerX, this->centerY, 2, 0, M_PI * 2); 
    cairo_fill(cairo);
  }

  cairo_set_source_rgb(cairo, 0, 0, 0);
  cairo_arc(cairo, 10, 10, 10, 0, M_PI * 2); 
  cairo_fill(cairo);  

  cairo_destroy(cairo);
  return surface;
}
