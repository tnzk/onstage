#include "item.hpp"

Item::Item(std::string name)
{
  this->name = name;
  rsvg_init();
  rsvg_term();
}

Item::~Item()
{
}

bool Item::Render(cairo_t* cairo)
{
  cairo_select_font_face(cairo, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cairo, 32.0);
  cairo_set_source_rgb(cairo, 0.0, 0.0, 1.0);
  cairo_move_to(cairo, (float)30, 100.0);
  cairo_show_text(cairo, this->name.c_str());

  rsvg_init();
  rsvg = rsvg_handle_new_from_file("svgs/bg-s02-b1-momoroom.svg", NULL);
  rsvg_handle_render_cairo(this->rsvg, cairo);
  rsvg_handle_free(this->rsvg);
  rsvg_term();

  return true;
}
