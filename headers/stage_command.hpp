#ifndef COMMAND_HEADER

#define COMMAND_HEADER

#include "picojson.h"
#include "string"
class TheStage;

class IStageCommand
{
private:
  
public:
  virtual std::string Serialize() = 0;
  virtual bool Execute(TheStage&) = 0;
};

class StageCommandFactory
{
public:
  static IStageCommand* Create(picojson::value&);
};

#endif
