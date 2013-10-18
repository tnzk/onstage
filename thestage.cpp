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
  
  cairo_t* cr = cairo_create(surface);

  cairo_select_font_face (cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size (cr, 32.0);
  cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
  cairo_move_to (cr, (float)this->currentFrame, 50.0);
  cairo_show_text (cr, "Hello, world");

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
