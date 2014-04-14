
#include "stage_command_look_reset.hpp"
#include "thestage.hpp"
#include <sstream>

LookResetStageCommand::LookResetStageCommand(std::string param0)
{
  this->actorId = param0;
}

LookResetStageCommand::~LookResetStageCommand()
{
}

bool LookResetStageCommand::Execute(TheStage& stage)
{
  Actor* actor = dynamic_cast<Actor*>(stage.GetSymbol(this->actorId));
  actor->LookReset();
}

std::string LookResetStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"look_reset\", \"" << this->actorId << "\"]";
  return ss.str();
}
