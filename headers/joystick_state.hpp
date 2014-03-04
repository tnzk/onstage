#ifndef JOYSTICK_STATE_HEADER
#define JOYSTICK_STATE_HEADER

#include <string>
#include <map>
#include <vector>

class JoystickState
{
public:
  JoystickState(std::string);
  ~JoystickState();
  void ProcessEvent();
  enum class ButtonSymbol { X, Y, A, B, L1, L2, R1, R2,
                            START, SELECT, LHAT, RHAT };
  enum class AxisSymbol { LX, LY, RX, RY, CX, CY};
  std::pair<int, int> GetAxis(AxisSymbol, AxisSymbol);
private:
  int fd;
  std::map<ButtonSymbol, int> buttonMap;
  std::map<AxisSymbol, int> axisMap;
  std::vector<bool> buttons;
  std::vector<int> axis;
  int numberOfButtons;
  int numberOfAxis;
};


#endif
