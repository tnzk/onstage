#include "actor.hpp"

Actor::Actor(std::string name)
{
  this->name = name;
  this->SetPosition(640, 360);
}

Actor::~Actor()
{
}

bool Actor::Render(cairo_t* cairo, Camera* camera)
{
  double rx;
  double ry;
  camera->Translate(this->x, this->y, rx, ry);

  cairo_select_font_face(cairo, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cairo, 32.0);
  cairo_set_source_rgb(cairo, 0.0, 0.0, 1.0);
  cairo_move_to(cairo, (float)rx, ry);
  cairo_show_text(cairo, this->name.c_str());

  return true;
}

void Actor::SetScale(double scale) { this->scale = scale;}
double Actor::GetScale() { return this->scale;}
std::string Actor::GetName() { return this->name; }
void Actor::SetPosition(double x, double y)
{
  this->x = x;
  this->y = y;
}
void Actor::Move(double dx, double dy)
{
  this->SetPosition(this->x + dx, this->y + dy);
}
