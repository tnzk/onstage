#ifndef THESTAGE_HEADER

#define THESTAGE_HEADER

#include <cairo.h>
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
  void SetFps(int);
  void SetDuration(int);
  int GetDuration();
  int GetCurrentFrame();
  bool Execute(IStageCommand& command);
  bool Render(cairo_t*);
  bool Skip();
  void ShowVideoSetting();
  int skipUntil;
private:
  int width;
  int height;
  int currentFrame;
  int fps;
  int duration; // in frame
};

#endif

