#ifndef STAGE_VIEWER_HEADER
#define STAGE_VIEWER_HEADER

#include "thestage.hpp"
#include "user_control_context.hpp"

class StageViewer
{
public:
  StageViewer(TheStage* const);
  void Run();
  UserControlContext* controlContext; // TODO: Be private.
private:
  TheStage* thestage;
};

#endif
