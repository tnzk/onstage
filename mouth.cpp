#include "mouth.hpp"
#include <iostream>
#include <list>
#include <stdlib.h>

Mouth::Mouth(Symbol* symbol)
{
  this->symbol = symbol;

  // Am I doing anything wrong? Why'd this have to be so hard...

  std::map<std::string, std::list<IRenderable*>> facialTemp;
  for (IRenderable* renderable : this->symbol->layers) {
    std::string facialType = renderable->meta["facial-type"];
    if (facialType == "intermediate") {
      this->intermediates.push_back(renderable);
      continue;
    }
    auto mouthStylesIterator = facialTemp.find(facialType);
    auto mouthStyles = (mouthStylesIterator != facialTemp.end()) ? mouthStylesIterator->second : std::list<IRenderable*>();
    if (renderable->meta["mouth-style"] == "open") {
      mouthStyles.push_back(renderable);
    } else {
      mouthStyles.push_front(renderable);
    }
    facialTemp[facialType] = mouthStyles;
  }

  for (auto& element : facialTemp) {
    std::string facialType = element.first;
    std::list<IRenderable*> mouthStyleList = element.second;
    std::list<IRenderable*>::iterator it = mouthStyleList.begin();
    IRenderable* close = *it;
    IRenderable* open = *(std::next(it));
    this->facials.insert(std::make_pair(facialType, std::make_pair(close, open)));
  }

  // TODO: Determine the default facial by configuration
  this->ChangeFacial("smile");
  this->Shut();
}

bool Mouth::ChangeFacial(std::string facial)
{
  // Do nothing and returns false if no facial type registeredb
  if (this->facials.find(facial) != this->facials.end()) {
    this->Clear();
    this->currentFacial = this->facials[facial];
    return true;
  }
  return false;
}

bool Mouth::Open()
{
  this->Clear();
  this->currentFacial.second->isVisible = true;
  return true;
}

bool Mouth::Close()
{
  this->Clear();
  this->currentFacial.first->isVisible = true;
  return true;
}

IRenderable* Mouth::Intermediate()
{
  int index = rand() % this->intermediates.size();
  IRenderable* intermediate = this->intermediates[index];
  this->Clear();
  intermediate->isVisible = true;
  return intermediate;
}

void Mouth::Sync(int frame)
{
  this->symbol->Sync(frame);
  if (this->IsSpeaking()) {
    switch(frame % 8) {
    case 0: this->Open(); break;
    case 2: this->Intermediate(); break;
    case 4: this->Close(); break;
    case 6: this->Intermediate(); break;
    default: break;
    }
  }
}

void Mouth::Clear()
{
  for (auto& layer: this->symbol->layers) {
    layer->isVisible = false;
  }
}

void Mouth::Speak()
{
  this->isSpeaking = true;
}

void Mouth::Shut()
{
  this->isSpeaking = false;
  this->Close();
}

bool Mouth::IsSpeaking()
{
  return this->isSpeaking;
}
