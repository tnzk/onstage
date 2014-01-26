#ifndef MOUTH_HEADER
#define MOUTH_HEADER

#include <string>
#include <vector>
#include <map>
#include "symbol.hpp"

class Mouth
{
public:
  Mouth(Symbol*);
  ~Mouth();
  void Speak();
  void Shut();
  bool Open();
  bool Close();
  bool ChangeFacial(std::string);
  void Sync(int);
  bool IsSpeaking();
private:
  bool isSpeaking;
  void Clear();
  IRenderable* Intermediate();
  Symbol* symbol;
  std::pair<IRenderable*, IRenderable*> currentFacial;
  std::map<std::string, std::pair<IRenderable*, IRenderable*>> facials;
  std::vector<IRenderable*> intermediates;
};


#endif
