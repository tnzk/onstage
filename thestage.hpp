#include "stage_command.hpp"

#ifndef THESTAGE_HEADER

#define THESTAGE_HEADER

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

