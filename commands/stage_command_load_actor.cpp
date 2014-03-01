#include "stage_command_load_actor.hpp"
#include <sstream>

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

std::string LoadActorStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"load_actor\", \"" << this->actorName << "\"]";
  return ss.str();
}
