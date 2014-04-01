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
  Actor(std::string id, std::string path);  
  void Walk(double dx, double dy);
  void Stop();
  bool LookAt(double rad, double distance);
  bool Eyeblows(double r);
  bool Eyeblows(double left, double right);
  void LeftHand(double rad, double distance);
  void RightHand(double rad, double distance);
  bool Speak();
  bool Shut();
  void Sync(int) override;
  bool IsSpeaking();
  void ChangeFacial(std::string);
private:
  bool isWalking;
  Head* head;
  std::pair<Arm*, Arm*> arms;
  std::tuple<double, double, double> walkingOrigin;
  double dx;
  double dy;
};

#endif
