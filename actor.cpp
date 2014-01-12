#include "actor.hpp"
#include <iostream>

bool Actor::Speak()
{
  std::cout << "im here" << std::endl;
  IRenderable* renderable = this->GetRenderable("mouth");
  if (renderable) {
    renderable->isVisible = false;
  } else {
    std::cout << "something went wrong" << std::endl;
  }
  return true;
}
