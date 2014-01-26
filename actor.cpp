#include "actor.hpp"
#include <iostream>

Actor::Actor(std::string name) : Symbol(name)
{
  IRenderable* head = this->GetRenderableById("head");
  if (head == NULL) {
    std::cout << "Error: No symbol whose name is head not found for " 
              << this->instanceId << ":"  << this->className << std::endl;
    // TODO: Abort
  }  
  this->head = new Head(dynamic_cast<Symbol*>(head));
}

bool Actor::Speak()
{
  this->head->Speak();
  return true;
}

bool Actor::Shut()
{
  this->head->Shut();
  return true;
}

bool Actor::LookAt(double rad, double distance)
{
  this->head->LookAt(rad, distance);
  return true;
}

bool Actor::Eyeblows(double r) { return this->Eyeblows(r, r); }
bool Actor::Eyeblows(double left, double right)
{
  return this->head->Eyeblows(left, right);
}

void Actor::Sync(int frame)
{
  // std::cout << "Actor::Sync" << std::endl;
  Symbol::Sync(frame);
  this->head->Sync(frame);
}

bool Actor::IsSpeaking()
{
  return this->head->IsSpeaking();
}

void Actor::ChangeFacial(std::string facial)
{
  std::map<std::string, double> tableFacialToEyeblowAngle;
  tableFacialToEyeblowAngle["sad"] = -0.4;
  tableFacialToEyeblowAngle["offensive"] = 0.4;
  tableFacialToEyeblowAngle["anger"] = 0.4;
  tableFacialToEyeblowAngle["smile"] = 0;
  double eyeblowAngle = tableFacialToEyeblowAngle[facial];
  this->Eyeblows(eyeblowAngle, -eyeblowAngle);

  this->head->ChangeFacial(facial);
}
