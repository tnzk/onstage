#ifndef JOYSTICK_EVENT_HEADER
#define JOYSTICK_EVENT_HEADER

#include <string>
#include <map>
#include <vector>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>

class JoystickEvent
{
public:
  JoystickEvent(struct js_event* e);
  ~JoystickEvent();
  enum class Type {AXIS, BUTTON};
  Type type;
  unsigned int number;
  int value;
  std::string ToString();
  bool IsButton();
  bool IsAxis();
private:
};


#endif
