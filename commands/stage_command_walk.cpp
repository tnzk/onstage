
#include "stage_command_walk.hpp"
#include "thestage.hpp"
#include <sstream>

WalkStageCommand::WalkStageCommand(std::string param0, double param1, double param2)
{
  this->actorId = param0;
  this->dx = param1;
  this->dy = param2;
}

WalkStageCommand::~WalkStageCommand()
{
}

bool WalkStageCommand::Execute(TheStage& stage)
{
  Actor* actor = dynamic_cast<Actor*>(stage.GetSymbol(this->actorId));
  actor->Stop(); // TODO: Is this correct?
  actor->Walk(this->dx, this->dy);
}

std::string WalkStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"walk\", \"" << this->actorId << "\", " << this->dx << ", " << this->dy << "]";
  return ss.str();
}
