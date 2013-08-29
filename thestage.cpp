#include "thestage.hpp"

TheStage::TheStage()
{
  this->width = 854;
  this->height = 480;
  this->currentFrame = 0;
  this->fps = 30;
  this->duration = 150;
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

bool TheStage::Execute(IStageCommand& command) const
{
  TheStage stage = *this;
  command.Execute(stage);
  return true;
}

bool TheStage::Render(unsigned char*)
{
  return true;
}

bool TheStage::Skip()
{
  return true;
}

