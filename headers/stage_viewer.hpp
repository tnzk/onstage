#ifndef STAGE_VIEWER_HEADER
#define STAGE_VIEWER_HEADER

#include "thestage.hpp"
#include "joystick_state.hpp"

class StageViewer
{
public:
  StageViewer(TheStage* const);
  void Run();
  JoystickState* joystick; // TODO: Be private.
private:
  TheStage* thestage;
};

#endif
