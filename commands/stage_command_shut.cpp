#include "stage_command_shut.hpp"
#include "actor.hpp"
#include "thestage.hpp"

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
