#ifndef STAGE_COMMAND_EYEBLOWS_HPP
#define STAGE_COMMAND_EYEBLOWS_HPP

#include <string>
#include "thestage.hpp"

class EyeblowsStageCommand : public IStageCommand
{
public:
  EyeblowsStageCommand(std::string, double, double);
  ~EyeblowsStageCommand();
  virtual bool Execute(TheStage&);
private:
  std::string targetName;
  double left;
  double right;
};

#endif
