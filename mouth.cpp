#include "mouth.hpp"
#include <iostream>
#include <list>

Mouth::Mouth(Symbol* symbol)
{
  this->symbol = symbol;

  // Am I doing anything wrong? Why'd this have to be so hard...

  std::map<std::string, std::list<IRenderable*>> facialTemp;
  for (IRenderable* renderable : this->symbol->layers) {
    std::string facialType = renderable->meta["facial-type"];
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

}

bool Mouth::ChangeFacial(std::string facial)
{
  this->currentFacial = this->facials[facial];
  return true;
}

bool Mouth::Open()
{
  this->currentFacial.first->isVisible = false;
  this->currentFacial.second->isVisible = true;
  return true;
}

bool Mouth::Close()
{
  this->currentFacial.first->isVisible = true;
  this->currentFacial.second->isVisible = false;
  return true;
}
