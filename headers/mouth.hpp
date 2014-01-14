#ifndef MOUTH_HEADER
#define MOUTH_HEADER

#include "symbol.hpp"

class Mouth
{
public:
  Mouth(Symbol*);
  ~Mouth();
  bool Open();
  bool Close();

private:
  Symbol* symbol;
  std::string symbolForOpen;
  std::string symbolForClose;
};


#endif
