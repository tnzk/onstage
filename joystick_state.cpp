#include "joystick_state.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <iostream>


JoystickState::JoystickState(std::string deviceName)
{
  this->fd = open(deviceName.c_str(), O_NONBLOCK | O_RDONLY);
  this->buttonMap[JoystickState::ButtonSymbol::X] = 0;
  this->buttonMap[JoystickState::ButtonSymbol::Y] = 1;
  this->buttonMap[JoystickState::ButtonSymbol::A] = 2;
  this->buttonMap[JoystickState::ButtonSymbol::B] = 3;
  this->buttonMap[JoystickState::ButtonSymbol::L1] = 4;
  this->buttonMap[JoystickState::ButtonSymbol::L2] = 6;
  this->buttonMap[JoystickState::ButtonSymbol::R1] = 5;
  this->buttonMap[JoystickState::ButtonSymbol::R2] = 7;
  this->buttonMap[JoystickState::ButtonSymbol::START] = 11;
  this->buttonMap[JoystickState::ButtonSymbol::SELECT] = 10;
  this->buttonMap[JoystickState::ButtonSymbol::LHAT] = 8;
  this->buttonMap[JoystickState::ButtonSymbol::RHAT] = 9;
  this->axisMap[JoystickState::AxisSymbol::LX] = 0;
  this->axisMap[JoystickState::AxisSymbol::LY] = 1;
  this->axisMap[JoystickState::AxisSymbol::RX] = 3;
  this->axisMap[JoystickState::AxisSymbol::RY] = 4;
  this->axisMap[JoystickState::AxisSymbol::CX] = 5;
  this->axisMap[JoystickState::AxisSymbol::CY] = 6;

  this->numberOfButtons = 0;
  this->numberOfAxis = 0;
  struct js_event e;
  while (read(this->fd, &e, sizeof(e)) > 0) {
    if (e.type & JS_EVENT_INIT) {
      if (e.type & JS_EVENT_BUTTON) this->numberOfButtons++;
      if (e.type & JS_EVENT_AXIS) this->numberOfAxis++;
    } else {
      // Discard anything else INIT event.
    }
  }
  if (errno != EAGAIN) {
    // TODO: Anything else EAGAIN should be taken care of as a real error.
  }
  this->buttons.resize(this->numberOfButtons, false);
  this->axis.resize(this->numberOfAxis, 0);
}

JoystickState::~JoystickState()
{
}

std::vector<JoystickEvent> JoystickState::ProcessEvent()
{
  std::vector<JoystickEvent> events;
  struct js_event e;
  while (read(this->fd, &e, sizeof(e)) > 0) {
    JoystickEvent ev(&e);
    if (e.type & JS_EVENT_BUTTON) {
      this->buttons[e.number] = e.value == 1;
    }
    if (e.type & JS_EVENT_AXIS) {
      this->axis[e.number] = e.value;
    }
    events.push_back(ev);
  }
  if (errno != EAGAIN) {
    // TODO: Anything else EAGAIN should be taken care of as a real error.
  }
  return events;
}

int JoystickState::GetAxis(AxisSymbol symbol)
{
  return this->axis[this->axisMap[symbol]];
}

std::pair<int, int> JoystickState::GetAxis(AxisSymbol xSymbol, AxisSymbol ySymbol) 
{
  int x = this->axis[this->axisMap[xSymbol]];
  int y = this->axis[this->axisMap[ySymbol]];
  return std::make_pair(x, y);
}

bool JoystickState::Prove(JoystickEvent& event, JoystickState::ButtonSymbol symbol, bool isPressed)
{
  return event.IsButton() && event.number == this->buttonMap[symbol] && (event.value == 1) == isPressed;
}

bool JoystickState::Prove(JoystickEvent& event, JoystickState::AxisSymbol symbol)
{
  return event.IsAxis() && event.number == this->axisMap[symbol];
}
