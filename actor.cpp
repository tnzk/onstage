#include "actor.hpp"
#include <iostream>

Actor::Actor(std::string name) : Symbol(name)
{
  IRenderable* head = this->GetRenderable("head");
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

bool Actor::LookAt(double rad, double distance)
{
  this->head->LookAt(rad, distance);
  return true;
}

void Actor::Sync(int frame)
{
  // std::cout << "Actor::Sync" << std::endl;
  Symbol::Sync(frame);
  this->head->Sync(frame);
}
