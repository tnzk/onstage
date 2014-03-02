
#include "stage_command_stop.hpp"
#include "thestage.hpp"
#include <sstream>

StopStageCommand::StopStageCommand(std::string param0)
{
  this->actorId = param0;
}

StopStageCommand::~StopStageCommand()
{
}

bool StopStageCommand::Execute(TheStage& stage)
{
  Actor* actor = dynamic_cast<Actor*>(stage.GetSymbol(this->actorId));
  actor->Stop();
}

std::string StopStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"stop\", \"" << this->actorId << "\"]";
  return ss.str();
}
