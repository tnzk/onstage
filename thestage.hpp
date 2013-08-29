#ifndef THESTAGE_HEADER

#define THESTAGE_HEADER

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
  bool Execute(IStageCommand& command) const;
  bool Render(unsigned char* buf);
  bool Skip();
  void ShowVideoSetting();
private:
  int width;
  int height;
  int currentFrame;
  int fps;
  int duration; // in frame
};

#endif

