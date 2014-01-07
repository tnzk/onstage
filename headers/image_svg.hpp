#ifndef IMAGE_SVG_HEADER
#define IMAGE_SVG_HEADER

#include "renderable.hpp"
#include <cairo.h>
#include <string>
#include <librsvg/rsvg.h>
#include <librsvg/rsvg-cairo.h>

class ImageSvg : public IRenderable
{
public:
  ImageSvg(std::string);
  ~ImageSvg();
  virtual cairo_surface_t* Render(double scale);
private:
  RsvgHandle* rsvg;

};

#endif
