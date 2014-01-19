#ifndef STAGE_COMMAND_LOOKAT_HPP
#define STAGE_COMMAND_LOOKAT_HPP

#include <string>
#include "thestage.hpp"

class LookatStageCommand : public IStageCommand
{
public:
  LookatStageCommand(std::string, double, double);
  ~LookatStageCommand();
  virtual bool Execute(TheStage&);
private:
  std::string targetName;
  double rad;
  double distance;
};

#endif
