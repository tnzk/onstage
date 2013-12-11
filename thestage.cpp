#include "thestage.hpp"
#include <stdlib.h>
#include <algorithm>

TheStage::TheStage()
{
  this->width = 1280;
  this->height = 720;
  this->currentFrame = 0;
  this->fps = 30;
  this->duration = 150;
  this->skipUntil = 0;
  this->primaryCameraId = this->AddCamera(this->width / 2, this->height / 2, 1);
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


  for(std::list<IActable*>::reverse_iterator it = this->actables.rbegin(); it != this->actables.rend(); ++it) {
    IActable* actable = *it;
    actable->Render(cairo, this->GetPrimaryCamera());
  }
  
  std::cout << this->currentFrame << "th frame rendered." << std::endl;
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

void TheStage::RegisterActable(std::string name, IActable* actable)
{
  this->actables.push_back(actable);
}

void TheStage::RegisterActor(std::string name, Actor* actor)
{
  this->RegisterActable(name, actor);
}

void TheStage::RegisterItem(std::string name, Item* item)
{
  this->RegisterActable(name, item);
}

IActable* TheStage::GetActable(std::string name)
{
  std::list<IActable*>::iterator it;
  it = std::find_if(this->actables.begin(), this->actables.end(), [name](IActable* actable) { return actable->GetName() == name; });
  return *it;
}

int TheStage::AddCamera(double x, double y, double zoom)
{
  Camera* camera = new Camera();
  camera->SetPosition(x, y);
  camera->SetZoom(zoom);
  camera->SetResolution(this->width, this->height);
  this->cameras.push_back(camera);
  return this->cameras.size() - 1;
}

Camera* TheStage::GetPrimaryCamera()
{
  return this->cameras[this->primaryCameraId];
}
