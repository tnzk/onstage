#include "thestage.hpp"
#include <stdlib.h>

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

int TheStage::GetDuration() { return this->duration; }

bool TheStage::Execute(IStageCommand& command) 
{
  command.Execute(*this);
  return true;
}

int TheStage::GetCurrentFrame() { return this->currentFrame; }

bool TheStage::Render(unsigned char* buffer, int size)
{
  std::cout << this->currentFrame << "th frame rendered." << std::endl;
  for(int i = 0; i < size; i++)
    buffer[i] = i;
  this->currentFrame++;
  return true;
}

bool TheStage::Skip()
{
  std::cout << this->currentFrame << "th frame skipped." << std::endl;
  this->currentFrame++;
  return true;
}

unsigned char* TheStage::AllocateBuffer(int* frameSize)
{
  *frameSize = this->width * this->height * 4;
  return (unsigned char*)malloc(*frameSize);
}

void TheStage::FreeBuffer(unsigned char* buffer)
{
  if(buffer) free(buffer);
}
