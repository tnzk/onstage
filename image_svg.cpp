#include "image_svg.hpp"
#include <math.h>
#include <sstream>

ImageSvg::ImageSvg(std::string svgPath)
{
  std::stringstream ss;
  ss << "svgs/" << svgPath;

  this->rsvg = rsvg_handle_new_from_file(ss.str().c_str(), NULL);

  RsvgDimensionData dimention;
  rsvg_handle_get_dimensions(rsvg, &dimention);
  this->width  = dimention.width;
  this->height = dimention.height;
}

ImageSvg::~ImageSvg()
{
  rsvg_handle_free(this->rsvg);
}

cairo_surface_t* ImageSvg::Render(double scale)
{
  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                                        this->width * scale,
                                                        this->height * scale);
  cairo_t* cairo = cairo_create(surface);
  cairo_scale(cairo, scale, scale);
  rsvg_handle_render_cairo(this->rsvg, cairo);

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

  cairo_destroy(cairo);
  return surface;
}
