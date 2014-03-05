#ifndef USER_CONTROL_STATE_HEADER
#define USER_CONTROL_STATE_HEADER

#include <string>

class UserControlState
{
public:
  UserControlState();
  ~UserControlState();
  enum class Symbol { X, Y, A, B, L1, L2, R1, R2,
                      UP, RIGHT, DOWN, LEFT,
                      START, SELECT, LHAT, RHAT };
  enum class State { Global, Selector, Loader, Camera, Facial, Behaviour};
  void Input(Symbol);
  State GetState();
  static std::string StateToString(State state);
private:
  State state;
  State previousState;
  int index;
};


#endif
