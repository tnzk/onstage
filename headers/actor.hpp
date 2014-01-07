#ifndef ACTOR_HEADER

#define ACTOR_HEADER

#include <cairo.h>
#include <string>
#include "symbol.hpp"
#include "camera.hpp"

enum ActorFace 
{
  Smily,
  Anger,
  Sad
};

class Actor : public ISymbol
{
public:
  Actor(std::string);
  ~Actor();
  virtual cairo_surface_t* Render(double);
  virtual void SetScale(double);
  virtual double GetScale();
  virtual std::string GetName();
  virtual void SetPosition(double, double);
  virtual void Move(double, double);
  bool Walk(double x, double y);
  bool LookAt(double r, double distance);
  bool Eyeblows(double r);
  bool Hand(double left_r,  double left_distance, 
            double right_r, double right_distance);
  bool Speak();
  bool Shut();
private:
  bool isSpeaking;
  bool isWalking;
};

#endif
