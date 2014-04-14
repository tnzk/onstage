#ifndef STAGE_COMMAND_LOOK_RESET_HPP
#define STAGE_COMMAND_LOOK_RESET_HPP

#include <string>
#include "thestage.hpp"

class LookResetStageCommand : public IStageCommand
{
public:
  LookResetStageCommand(std::string);
  ~LookResetStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  // Declare here private members for paramters.
  std::string actorId;
};

#endif
