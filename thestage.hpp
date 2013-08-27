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
  bool Execute(IStageCommand& command) const;
  bool Render(unsigned char* buf);
  bool Skip();
private:
  int width;
  int height;
  int frame;
};

#endif

