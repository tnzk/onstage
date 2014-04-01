#include "stage_command_load_actor.hpp"
#include <sstream>

LoadActorStageCommand::LoadActorStageCommand(std::string id, std::string path){

  this->instanceId = id;
  this->symbolPath = path;
}

LoadActorStageCommand::~LoadActorStageCommand()
{
}

bool LoadActorStageCommand::Execute(TheStage& stage)
{
  Actor* actor = new Actor(this->instanceId, this->symbolPath);
  stage.RegisterActor(this->instanceId, actor);
  std::cout << this->instanceId << "(" << this->symbolPath <<") enters." << std::endl;
}

std::string LoadActorStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"load_actor\", \"" << this->instanceId << "\", \"" << this->symbolPath << "\"]";
  return ss.str();
}
