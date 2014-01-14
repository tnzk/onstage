#include "mouth.hpp"
#include <iostream>

Mouth::Mouth(Symbol* symbol)
{
  this->symbol = symbol;
  this->symbolForOpen = "mouth-04";
  this->symbolForClose = "mouth-01";
}

bool Mouth::Open()
{
  IRenderable* openMouth = this->symbol->GetRenderable(this->symbolForOpen);
  IRenderable* closeMouth = this->symbol->GetRenderable(this->symbolForClose);
  
  openMouth->isVisible = true;
  closeMouth->isVisible = false;
}

bool Mouth::Close()
{
  IRenderable* openMouth = this->symbol->GetRenderable(this->symbolForOpen);
  IRenderable* closeMouth = this->symbol->GetRenderable(this->symbolForClose);
  
  openMouth->isVisible = false;
  closeMouth->isVisible = true;
}
