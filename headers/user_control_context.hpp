#ifndef USER_CONTROL_CONTEXT_HEADER
#define USER_CONTROL_CONTEXT_HEADER

#include <string>
#include <vector>
#include "actor.hpp"
#include "thestage.hpp"
#include "stage_command.hpp"
#include "user_control_state.hpp"
#include "joystick_state.hpp"

class UserControlContext
{
public:
  UserControlContext(std::string deviceName, TheStage* stage);
  ~UserControlContext();
  std::vector<IStageCommand*> ProcessInput();
  std::string ToString();
  void ChangeTargetActor(std::string); // TODO: should be public? who cares?
  std::string GetTargetActor();
  UserControlState* controlState;
private:
  JoystickState* joystick;
  TheStage* stage;
  std::string targetId;
};


#endif
