#include "user_control_state.hpp"

UserControlState::UserControlState()
{
  this->state = UserControlState::State::Global;
}

UserControlState::~UserControlState()
{
}

void UserControlState::Input(UserControlState::Symbol symbol)
{
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
