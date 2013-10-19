#include "thestage.hpp"
#include <stdlib.h>

TheStage::TheStage()
{
  this->width = 854;
  this->height = 480;
  this->currentFrame = 0;
  this->fps = 30;
  this->duration = 150;
  this->skipUntil = 0;
}

void TheStage::ShowVideoSetting()
{
  std::cout << "== Video setting ====" << std::endl;
  std::cout << "     FPS: " << this->fps << std::endl;
  std::cout << "duration: " << this->duration << " frames("
            << this->duration / this->fps << "s)" << std::endl;
  std::cout << "   width: " << this->width << std::endl;
  std::cout << "  height: " << this->height << std::endl;
}

void TheStage::SetResolution(int width, int height)
{
  this->width = width;
  this->height = height;
}

void TheStage::SetFps(int fps)
{
  if(fps > 0) this->fps = fps;
}

void TheStage::SetDuration(int duration)
{
  this->duration = duration;
}

int TheStage::GetDuration() { return this->duration; }

bool TheStage::Execute(IStageCommand& command) 
{
  command.Execute(*this);
  return true;
}

int TheStage::GetCurrentFrame() { return this->currentFrame; }

bool TheStage::Render(cairo_surface_t* surface)
{
  std::cout << this->currentFrame << "th frame rendered." << std::endl;
  this->currentFrame++;
  
  cairo_t* cairo = cairo_create(surface);

  // Clear the surface
  cairo_set_source_rgb(cairo, 1.0, 1.0, 1.0);
  cairo_paint(cairo);

  cairo_select_font_face(cairo, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cairo, 32.0);
  cairo_set_source_rgb(cairo, 0.0, 0.0, 1.0);
  cairo_move_to(cairo, (float)this->currentFrame, 50.0);
  cairo_show_text(cairo, "Hello, world");

  std::map<std::string, Actor>::iterator it = this->actors.begin();
  for(; it != this->actors.end(); ++it) {
    Actor actor = it->second;
    actor.Render(cairo);
  }

  return true;
}

bool TheStage::Skip()
{
  std::cout << this->currentFrame << "th frame skipped." << std::endl;
  this->currentFrame++;
  return true;
}

int TheStage::GetResolutionWidth() { return this->width; }
int TheStage::GetResolutionHeight() { return this->height; }

void TheStage::RegisterActor(std::string name, Actor& actor)
{
  this->actors.insert(std::pair<std::string, Actor>(name, actor));
}
