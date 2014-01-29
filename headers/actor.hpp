#ifndef ACTOR_HEADER
#define ACTOR_HEADER

#include <cairo.h>
#include <string>
#include "symbol.hpp"
#include "head.hpp"
#include "arm.hpp"

enum ActorFace 
{
  Smily,
  Anger,
  Sad
};

class Actor : public Symbol
{
public:
  Actor(std::string name);

  bool Walk(double x, double y);
  bool LookAt(double rad, double distance);
  bool Eyeblows(double r);
  bool Eyeblows(double left, double right);
  bool Hand(double leftAngle,  double leftDistance, 
            double rightAngle, double rightDistance);
  bool Speak();
  bool Shut();
  void Sync(int) override;
  bool IsSpeaking();
  void ChangeFacial(std::string);
private:
  bool isWalking;
  Head* head;
  std::pair<Arm*, Arm*> arms;
};

#endif
