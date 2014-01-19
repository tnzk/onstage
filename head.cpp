#include "head.hpp"
#include <iostream>
#include <math.h>

Head::Head(Symbol* symbol)
{
  this->symbol = symbol;
  Symbol* face = dynamic_cast<Symbol*>(this->symbol->GetRenderable("face"));

  IRenderable* mouth = face->GetRenderable("mouth");
  if (mouth == NULL) {
    std::cout << "Error: No symbol whose name is mouth not found for " 
              << face->instanceId << ":"  << face->className << std::endl;
    // TODO: Abort
  }
  this->mouth = new Mouth(dynamic_cast<Symbol*>(mouth));

  IRenderable* eyes = face->GetRenderable("eyes");
  if (eyes == NULL) {
    std::cout << "Error: No symbol whose name is eyes not found for " 
              << face->instanceId << ":"  << face->className << std::endl;
    // TODO: Abort
  }
  this->eyes = new Eyes(dynamic_cast<Symbol*>(eyes));

  this->eyes->LookAt(M_PI, 100);
  this->eyes->LookAt(M_PI, 100);
}

bool Head::Speak()
{
  std::cout << "Head speaks." << std::endl;
  this->mouth->Open();
}

void Head::Sync(int frame)
{
  this->symbol->Sync(frame);
  this->mouth->Sync(frame);
}
