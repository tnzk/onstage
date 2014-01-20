#include "head.hpp"
#include <iostream>
#include <math.h>

Head::Head(Symbol* symbol)
{
  this->symbol = symbol;
  Symbol* face = dynamic_cast<Symbol*>(this->symbol->GetRenderableById("face"));

  IRenderable* mouth = face->GetRenderableById("mouth");
  if (mouth == NULL) {
    std::cout << "Error: No symbol whose name is mouth not found for " 
              << face->instanceId << ":"  << face->className << std::endl;
    // TODO: Abort
  }
  this->mouth = new Mouth(dynamic_cast<Symbol*>(mouth));

  IRenderable* eyes = face->GetRenderableById("eyes");
  if (eyes == NULL) {
    std::cout << "Error: No symbol whose name is eyes not found for " 
              << face->instanceId << ":"  << face->className << std::endl;
    // TODO: Abort
  }
  this->eyes = new Eyes(dynamic_cast<Symbol*>(eyes));
}

bool Head::Speak()
{
  std::cout << "Head speaks." << std::endl;
  this->mouth->Open();
}

bool Head::LookAt(double rad, double distance)
{
  this->eyes->LookAt(rad, distance);
  return true;
}

void Head::Sync(int frame)
{
  this->symbol->Sync(frame);
  this->mouth->Sync(frame);
}
