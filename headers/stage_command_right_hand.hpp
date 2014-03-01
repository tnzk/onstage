#ifndef STAGE_COMMAND_RIGHT_HAND_HPP
#define STAGE_COMMAND_RIGHT_HAND_HPP

#include <string>
#include "thestage.hpp"

class RightHandStageCommand : public IStageCommand
{
public:
  RightHandStageCommand(std::string, double, double);
  ~RightHandStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  std::string actorId;
  double rad;
  double distance;
};

#endif
