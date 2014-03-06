#include "user_control_state.hpp"

UserControlState::UserControlState()
{
  this->state = UserControlState::State::Global;
}

UserControlState::~UserControlState()
{
}

bool UserControlState::Prove(JoystickEvent& event, JoystickEvent::Type type, unsigned int number, int value)
{
  return (event.type == JoystickEvent::Type::BUTTON && event.number == number && event.value);
}

void UserControlState::Input(JoystickState& state, JoystickEvent& event)
{
  switch(this->state) {
  case UserControlState::State::Global:
    if (state.Prove(event, JoystickState::ButtonSymbol::X, true)) {
      this->ChangeStateTo(UserControlState::State::Camera);
    }
    break;
  case UserControlState::State::Camera:
    if (state.Prove(event, JoystickState::ButtonSymbol::Y, true)) {
      this->ChangeStateTo(UserControlState::State::Loader);
    }
    break;
  case UserControlState::State::Loader:
    if (state.Prove(event, JoystickState::ButtonSymbol::A, true)) {
      this->ChangeStateTo(UserControlState::State::Global);
    }
    break;
  }
}

void UserControlState::ChangeStateTo(UserControlState::State newState)
{
  this->previousState = this->state;
  this->state = newState;
}

UserControlState::State UserControlState::GetState()
{
  return this->state;
}

std::string UserControlState::StateToString(UserControlState::State state)
{
  switch(state) {
  case UserControlState::State::Global:    return "Global";
  case UserControlState::State::Selector:  return "Selector";
  case UserControlState::State::Loader:    return "Loader";
  case UserControlState::State::Camera :   return "Camera";
  case UserControlState::State::Facial:    return "Facial";
  case UserControlState::State::Behaviour: return "Behaviour";
  }
  return "Unknown";
}
