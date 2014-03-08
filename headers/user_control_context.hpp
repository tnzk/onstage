#ifndef USER_CONTROL_CONTEXT_HEADER
#define USER_CONTROL_CONTEXT_HEADER

#include <string>
#include <vector>
#include "stage_command.hpp"
#include "user_control_state.hpp"
#include "joystick_state.hpp"

class UserControlContext
{
public:
  UserControlContext(std::string deviceName);
  ~UserControlContext();
  std::vector<IStageCommand*> ProcessInput();
  std::string ToString();
  UserControlState* controlState;
private:
  JoystickState* joystick;
};


#endif
