#include "stage_command.hpp"

#ifndef THESTAGE_HEADER

#define THESTAGE_HEADER

enum StageState
{
  StateRendering
};

class TheStage
{
public:
  bool Execute(IStageCommand&) const;
  bool Render(unsigned char*);
  bool Skip();
private:
  int width;
  int height;
  int frame;
};

#endif

