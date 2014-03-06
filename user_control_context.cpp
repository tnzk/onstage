#include "user_control_context.hpp"
#include <sstream>

UserControlContext::UserControlContext(std::string deviceName)
{
  this->joystick = new JoystickState(deviceName);
  this->controlState = new UserControlState();
}

UserControlContext::~UserControlContext() {}

std::vector<IStageCommand> UserControlContext::ProcessInput() 
{
  std::vector<IStageCommand> commands;
  auto events = this->joystick->ProcessEvent();
  for (auto ev : events) {
    this->controlState->Input(*this->joystick, ev);
  }
  return commands;
}

std::string UserControlContext::ToString()
{
  std::string stateString = UserControlState::StateToString(this->controlState->GetState());

  std::stringstream ss;
  ss << "State: " << stateString;
  return ss.str();
}
