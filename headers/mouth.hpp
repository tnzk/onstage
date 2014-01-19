#ifndef MOUTH_HEADER
#define MOUTH_HEADER

#include <string>
#include <map>
#include "symbol.hpp"

class Mouth
{
public:
  Mouth(Symbol*);
  ~Mouth();
  bool Open();
  bool Close();
  bool ChangeFacial(std::string);
  void Sync(int);

private:
  Symbol* symbol;
  std::pair<IRenderable*, IRenderable*> currentFacial;
  std::map<std::string, std::pair<IRenderable*, IRenderable*>> facials;
};


#endif
