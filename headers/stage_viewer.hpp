#ifndef STAGE_VIEWER_HEADER
#define STAGE_VIEWER_HEADER

#include "thestage.hpp"

class StageViewer
{
public:
  StageViewer(TheStage* const);
  void Run();
private:
  TheStage* thestage;
};

#endif
