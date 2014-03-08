#ifndef USER_CONTROL_STATE_HEADER
#define USER_CONTROL_STATE_HEADER

#include <string>
#include "joystick_event.hpp"
#include "joystick_state.hpp"

class UserControlState
{
public:
  UserControlState();
  ~UserControlState();
  enum class State { Global, Selector, Loader, Camera, Facial, Behaviour};
  void Input(JoystickState&, JoystickEvent&);
  State GetState();
  static std::string StateToString(State state);
  int index;
private:
  bool Prove(JoystickEvent&, JoystickEvent::Type, unsigned int, int);
  void BackState();
  void ChangeStateTo(State);
  State state;
  State previousState;
};


#endif
