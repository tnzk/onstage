#include "joystick_event.hpp"
#include <sstream>

JoystickEvent::JoystickEvent(struct js_event* e)
{
  this->value = e->value;
  this->number = e->number;
  this->type = (e->type & JS_EVENT_BUTTON) ? JoystickEvent::Type::BUTTON : JoystickEvent::Type::AXIS;
}

JoystickEvent::~JoystickEvent()
{
}

bool JoystickEvent::IsButton()
{
  return this->type == JoystickEvent::Type::BUTTON;
}

bool JoystickEvent::IsAxis()
{
  return this->type == JoystickEvent::Type::AXIS;
}

std::string JoystickEvent::ToString()
{
  std::stringstream ss;
  ss << "type: " << (this->type == JoystickEvent::Type::BUTTON ? "Button" : "Axis")
     << ", number: " << this->number << ", value:" << this->value;
  return ss.str();
}
