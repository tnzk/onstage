#ifndef THESTAGE_HEADER

#define THESTAGE_HEADER

#include <cairo.h>
#include <map>
#include <string>
#include "actable.hpp"
#include "actor.hpp"
#include "item.hpp"
#include "camera.hpp"
#include "stage_command.hpp"

enum StageState
{
  Rendering
};

class TheStage
{
public:
  TheStage();
  void SetResolution(int, int);
  int GetResolutionWidth();
  int GetResolutionHeight();
  void SetFps(int);
  void SetDuration(int);
  int GetDuration();
  int GetCurrentFrame();
  bool Execute(IStageCommand& command);
  bool Render(cairo_surface_t*);
  bool Skip();
  void ShowVideoSetting();
  void RegisterActor(std::string, Actor*);
  void RegisterItem(std::string, Item*);
  IActable* GetActable(std::string name);
  int skipUntil;
private:
  int width;
  int height;
  int currentFrame;
  int fps;
  int duration; // in frame
  std::map<std::string, Actor*> actors;
  std::map<std::string, Item*> items;
  int primaryCameraId;
  std::vector<Camera*> cameras;
};

#endif

