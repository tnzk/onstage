#ifndef HEAD_HEADER
#define HEAD_HEADER

#include "eyes.hpp"
#include "mouth.hpp"
#include "symbol.hpp"

class Head
{
public:
  Head(Symbol*);
  ~Head();
  bool LookAt(double rad, double distance);
  void LookReset();
  bool Eyeblows(double left, double right);
  bool Hand(double left_r,  double left_distance, 
            double right_r, double right_distance);
  bool Speak();
  bool Shut();
  void Sync(int);
  bool IsSpeaking();
  void ChangeFacial(std::string);
private:
  std::pair<double, double> basePosition;
  bool isSpeaking;
  Symbol* symbol;
  Mouth* mouth;
  Eyes* eyes;
  std::pair<IRenderable*, IRenderable*> eyeblows;
};


#endif
