#ifndef ACTOR_HEADER
#define ACTOR_HEADER

#include <cairo.h>
#include <string>
#include "symbol.hpp"
#include "head.hpp"

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
  bool Hand(double left_r,  double left_distance, 
            double right_r, double right_distance);
  bool Speak();
  bool Shut();
  void Sync(int) override;
  bool IsSpeaking();
  void ChangeFacial(std::string);
private:
  bool isWalking;
  Head* head;
};

#endif
