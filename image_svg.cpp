#include "image_svg.hpp"
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
  cairo_t* cairoInternal = cairo_create(surface);
  cairo_scale(cairoInternal, scale, scale);
  rsvg_handle_render_cairo(this->rsvg, cairoInternal);
  cairo_destroy(cairoInternal);
  return surface;
}
