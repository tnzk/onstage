#include "actor.hpp"
#include <iostream>
#include <tuple>
#include <math.h>

Actor::Actor(std::string id, std::string path) : Symbol(id, path)
{
  IRenderable* head = this->GetRenderableById("head");
  if (head == NULL) {
    std::cout << "Error: No symbol whose name is head not found for " 
              << this->instanceId << ":"  << this->className << std::endl;
    // TODO: Abort
  }  
  this->head = new Head(dynamic_cast<Symbol*>(head));

  IRenderable* armLeft = this->GetRenderableById("arm-left");
  if (armLeft == NULL) {
    std::cout << "Error: No symbol whose name is arm-left not found for " 
              << this->instanceId << ":"  << this->className << std::endl;
    // TODO: Abort
  }
  this->arms.first = new Arm(dynamic_cast<Symbol*>(armLeft), "left");

  IRenderable* armRight = this->GetRenderableById("arm-right");
  if (armRight == NULL) {
    std::cout << "Error: No symbol whose name is arm-right not found for " 
              << this->instanceId << ":"  << this->className << std::endl;
    // TODO: Abort
  }
  this->arms.second = new Arm(dynamic_cast<Symbol*>(armRight), "right");
  this->dx = 0;
  this->dy = 0;
  this->isWalking = false;
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
  Symbol::Sync(frame);
  this->head->Sync(frame);

  // TODO: must be done by something more general.
  IRenderable* head = this->GetRenderableById("head");
  if (head) {
    IRenderable* backHair = this->GetRenderableById("back-hair");
    if (backHair) {
      backHair->x = head->x;
      backHair->y = head->y;
      backHair->angle = head->angle;
    }
    IRenderable* foreHair = this->GetRenderableById("fore-hair");
    if (foreHair) {
      foreHair->x = head->x;
      foreHair->y = head->y;
      foreHair->angle = head->angle;
    }
  }  


  if (this->isWalking) {
    this->walkingOrigin = std::make_tuple(std::get<0>(this->walkingOrigin) + this->dx,
					  std::get<1>(this->walkingOrigin) + this->dy,
					  std::get<2>(this->walkingOrigin));
    this->x = std::get<0>(this->walkingOrigin);
    double frequency = frame * (sqrt(dx * dx + dy * dy) * 0.05 + 0.7);
    this->y = std::get<1>(this->walkingOrigin) + fabs(sin(frequency)) * 10.0;
    this->angle = std::get<2>(this->walkingOrigin) + sin(frequency) * M_PI / 90;
  }
}

void Actor::LeftHand(double rad, double distance)
{
  this->arms.first->SetPosition(rad, distance);
}

void Actor::RightHand(double rad, double distance)
{
  this->arms.second->SetPosition(rad, distance);
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

void Actor::Walk(double dx, double dy)
{
  if (!this->isWalking) {
    this->walkingOrigin = std::make_tuple(this->x, this->y, this->angle);
    this->dx = dx;
    this->dy = dy;
    this->isWalking = true;
  }
}

void Actor::Stop()
{
  if (this->isWalking) {
    this->dx = 0;
    this->dy = 0;
    this->isWalking = false;
    this->x = std::get<0>(this->walkingOrigin);
    this->y = std::get<1>(this->walkingOrigin);
    this->angle = std::get<2>(this->walkingOrigin);
  }
}
