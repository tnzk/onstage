#include "user_control_context.hpp"
#include <sstream>
#include "stage_command.hpp"
#include "stage_command_shut.hpp"
#include "stage_command_left_hand.hpp"
#include "stage_command_right_hand.hpp"

UserControlContext::UserControlContext(std::string deviceName)
{
  this->joystick = new JoystickState(deviceName);
  this->controlState = new UserControlState();
}

UserControlContext::~UserControlContext() {}

std::vector<IStageCommand*> UserControlContext::ProcessInput() 
{
  std::vector<IStageCommand*> commands;
  auto events = this->joystick->ProcessEvent();
  for (auto ev : events) {
    this->controlState->Input(*this->joystick, ev);
  }
  
  switch (this->controlState->GetState()) {
  case UserControlState::State::Behaviour:
    {
      auto leftAxis = this->joystick->GetAxis(JoystickState::AxisSymbol::LX, 
					      JoystickState::AxisSymbol::LY);
      if (leftAxis.first != 0 || leftAxis.second != 0) {
	double dx = leftAxis.first / 32767.0;
	double dy = leftAxis.second / -32767.0;
	double theta = atan2(dy, dx);
	double r = sqrt(dx * dx + dy * dy) * 150;
	IStageCommand* command = new LeftHandStageCommand("momo.json", theta, r);
	commands.push_back(command);
      }

      auto rightAxis = this->joystick->GetAxis(JoystickState::AxisSymbol::RX, 
					       JoystickState::AxisSymbol::RY);
      if (rightAxis.first != 0 || rightAxis.second != 0) {
	double dx = rightAxis.first / 32767.0;
	double dy = rightAxis.second / -32767.0;
	double theta = atan2(dy, dx);
	double r = sqrt(dx * dx + dy * dy) * 150;
	IStageCommand* command = new RightHandStageCommand("momo.json", theta, r);
	commands.push_back(command);
      }

    }
    break;
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
