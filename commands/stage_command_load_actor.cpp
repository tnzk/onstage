#include "stage_command_load_actor.hpp"

LoadActorStageCommand::LoadActorStageCommand(std::string name)
{
  this->actorName = name;
}

LoadActorStageCommand::~LoadActorStageCommand()
{
}

bool LoadActorStageCommand::Execute(TheStage& stage)
{
  std::cout << this->actorName << " enters." << std::endl;
  Actor* actor = new Actor(this->actorName);
  stage.RegisterActor(this->actorName, actor);
}
