#include "head.hpp"
#include <iostream>

Head::Head(Symbol* symbol)
{
  this->symbol = symbol;
}

bool Head::Speak()
{
  std::cout << "Head speaks." << std::endl;
  this->symbol->isVisible = false;
}
