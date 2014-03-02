#ifndef STAGE_COMMAND_WALK_HPP
#define STAGE_COMMAND_WALK_HPP

#include <string>
#include "thestage.hpp"

class WalkStageCommand : public IStageCommand
{
public:
  WalkStageCommand(std::string, double, double);
  ~WalkStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  std::string actorId;
  double dx;
  double dy;
};

#endif
