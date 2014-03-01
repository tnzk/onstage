#include "stage_command_shut.hpp"
#include "actor.hpp"
#include "thestage.hpp"
#include <sstream>

ShutStageCommand::ShutStageCommand(std::string actorId)
{
  this->actorId = actorId;
}

ShutStageCommand::~ShutStageCommand()
{
}

bool ShutStageCommand::Execute(TheStage& stage)
{
  Actor* actor = stage.GetActor(this->actorId);
  actor->Shut();
}

std::string ShutStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"shut\", \"" << this->actorId << "\"]";
  return ss.str();
}
