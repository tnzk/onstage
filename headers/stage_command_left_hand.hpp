#ifndef STAGE_COMMAND_LEFT_HAND_HPP
#define STAGE_COMMAND_LEFT_HAND_HPP

#include <string>
#include "thestage.hpp"

class LeftHandStageCommand : public IStageCommand
{
public:
  LeftHandStageCommand(std::string, double, double);
  ~LeftHandStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  std::string actorId;
  double rad;
  double distance;
};

#endif
