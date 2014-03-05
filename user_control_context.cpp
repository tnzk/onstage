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
  std::cout << events.size() << std::endl;
  for (auto ev : events) {
    std::cout << ev.ToString() << std::endl;
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
