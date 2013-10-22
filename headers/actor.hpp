#ifndef ACTOR_HEADER

#define ACTOR_HEADER

#include <cairo.h>
#include <string>
#include "actable.hpp"

enum ActorFace 
{
  Smily,
  Anger,
  Sad
};

class Actor : public IActable
{
public:
  Actor(std::string);
  ~Actor();
  virtual bool Render(cairo_t*);
  virtual void SetScale(double);
  virtual double GetScale();
  bool Walk(double x, double y);
  bool LookAt(double r, double distance);
  bool Eyeblows(double r);
  bool Hand(double left_r,  double left_distance, 
            double right_r, double right_distance);
  bool Speak();
  bool Shut();
private:
  std::string name;
  bool isSpeaking;
  bool isWalking;
};

#endif
