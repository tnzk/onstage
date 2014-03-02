#ifndef STAGE_COMMAND_STOP_HPP
#define STAGE_COMMAND_STOP_HPP

#include <string>
#include "thestage.hpp"

class StopStageCommand : public IStageCommand
{
public:
  StopStageCommand(std::string);
  ~StopStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  std::string actorId;
};

#endif
