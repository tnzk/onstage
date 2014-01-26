#include "head.hpp"
#include <iostream>
#include <math.h>
#include <stdlib.h>

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

  IRenderable* leftEyeblow = face->GetRenderableById("eyeblow-left");
  IRenderable* rightEyeblow =  face->GetRenderableById("eyeblow-right");
  this->eyeblows.first = leftEyeblow;
  this->eyeblows.second = rightEyeblow;

  this->basePosition.first = this->symbol->x;
  this->basePosition.second= this->symbol->y;
}

bool Head::Speak()
{
  this->mouth->Speak();
}

bool Head::Shut()
{
  this->mouth->Shut();
}

bool Head::IsSpeaking() { return this->mouth->IsSpeaking(); }

bool Head::LookAt(double rad, double distance)
{
  this->eyes->LookAt(rad, distance);
  return true;
}

bool Head::Eyeblows(double left, double right)
{
  if (this->eyeblows.first) this->eyeblows.first->angle = left;
  if (this->eyeblows.second) this->eyeblows.second->angle = right;
}

void Head::Sync(int frame)
{
  this->symbol->Sync(frame);
  this->mouth->Sync(frame);

  if (this->IsSpeaking()) {
    double bias = ((rand() % 5) - 2) * 0.01;
    this->symbol->y = this->basePosition.second + bias * 70;
    this->symbol->angle = (((frame / 2) % 3) - 1 ) * 0.05 + bias;
  } else {
    this->symbol->x = this->basePosition.first;
    this->symbol->y = this->basePosition.second;
    this->symbol->angle = 0;
  }
}

void Head::ChangeFacial(std::string facial)
{
  this->mouth->ChangeFacial(facial);
  this->mouth->Close();
}
