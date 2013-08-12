#include <librsvg/rsvg.h>
#include <librsvg/rsvg-cairo.h>
#include <cairo-svg.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
  cairo_t* cr3;
  cairo_surface_t* image;
    
  RsvgHandle* r_svg;
  RsvgError rs_err;
  RsvgDimensionData svgdim;
    
  cairo_matrix_t matrix;
    
  rsvg_init();
  r_svg = rsvg_handle_new_from_file(argv[1], NULL);
  rsvg_handle_get_dimensions(r_svg, &svgdim);

  int width = svgdim.width;
  int height = svgdim.height;
  unsigned char* buf = (unsigned char*)malloc(width * height * 4);

  image = cairo_image_surface_create_for_data(buf, CAIRO_FORMAT_ARGB32, width, height, width * 4);
  cr3 = cairo_create(image);
    
  cairo_set_source_rgb(cr3, 1.0, 0.0, 0.0);
  cairo_paint(cr3);
        
  rsvg_handle_render_cairo(r_svg, cr3);
    
  cairo_surface_write_to_png(image, "output.png");

  rsvg_handle_free(r_svg);
  rsvg_term();

  cairo_destroy(cr3);
  cairo_surface_destroy(image);

  free(buf);
    
  return 0;
}
