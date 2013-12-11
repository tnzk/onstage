#include "actor.hpp"

Actor::Actor(std::string name)
{
  this->name = name;
}

Actor::~Actor()
{
}

bool Actor::Render(cairo_t* cairo, Camera* camera)
{
  cairo_select_font_face(cairo, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cairo, 32.0);
  cairo_set_source_rgb(cairo, 0.0, 0.0, 1.0);
  cairo_move_to(cairo, (float)30, 100.0);
  cairo_show_text(cairo, this->name.c_str());

  return true;
}

void Actor::SetScale(double scale) { this->scale = scale;}
double Actor::GetScale() { return this->scale;}
std::string Actor::GetName() { return this->name; }
