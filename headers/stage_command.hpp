#ifndef COMMAND_HEADER

#define COMMAND_HEADER

#include "picojson.h"
class TheStage;

class IStageCommand
{
private:
  
public:
  virtual bool Execute(TheStage&) = 0;
};

class StageCommandFactory
{
public:
  static IStageCommand* Create(picojson::value&);
};

#endif
