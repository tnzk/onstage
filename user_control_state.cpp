#include "user_control_state.hpp"
#include <limits.h>
#include <iostream>

UserControlState::UserControlState()
{
  this->previousState = UserControlState::State::Global;
  this->state = UserControlState::State::Global;
  this->index = 0;
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
  if (state.Prove(event, JoystickState::ButtonSymbol::START, true)) {
    if (this->state == UserControlState::State::Global) {
      this->BackState();
    } else {
      this->ChangeStateTo(State::Global);
    }
  }

  switch (this->state) {
  case UserControlState::State::Global:
    static std::vector<UserControlState::State> menuItems { UserControlState::State::Selector,
                                                            UserControlState::State::Loader,
                                                            UserControlState::State::Camera,
                                                            UserControlState::State::Behaviour};
    if (state.Prove(event, JoystickState::AxisSymbol::CY)) {
      int cyValue = event.value;
      // TODO: The value of a joystick event would always be from SHORT_MIN to SHORT_MAX.
      if (cyValue >  100) this->index++; 
      if (cyValue < -100) this->index--;
      
      if (this->index > menuItems.size()) this->index = 0;
      if (this->index < 0) this->index = menuItems.size();
    }
    if (state.Prove(event, JoystickState::ButtonSymbol::A, true)) {
      if (this->index == menuItems.size()) {
	this->BackState();
      } else {
	this->ChangeStateTo(menuItems[this->index]);
      }
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
  case UserControlState::State::Behaviour:
    if (state.Prove(event, JoystickState::ButtonSymbol::L1, true)) {
      this->ChangeStateTo(UserControlState::State::Facial);
    }
    break;
  case UserControlState::State::Facial:
    if (state.Prove(event, JoystickState::ButtonSymbol::L1, true)) {
      this->ChangeStateTo(UserControlState::State::Behaviour);
    }
    break;
  }
}

void UserControlState::ChangeStateTo(UserControlState::State newState)
{
  this->previousState = this->state;
  this->state = newState;
  this->index = 0;
}

void UserControlState::BackState()
{
  this->ChangeStateTo(this->previousState);
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
