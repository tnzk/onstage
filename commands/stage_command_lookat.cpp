#include "stage_command_lookat.hpp"
#include "thestage.hpp"
#include <sstream>

LookatStageCommand::LookatStageCommand(std::string targetName, double rad, double distance)
{
  this->targetName = targetName;
  this->rad = rad;
  this->distance = distance;
}

LookatStageCommand::~LookatStageCommand()
{
}

bool LookatStageCommand::Execute(TheStage& stage)
{
  Actor* actor = dynamic_cast<Actor*>(stage.GetSymbol(this->targetName));
  actor->LookAt(this->rad, this->distance);
}

std::string LookatStageCommand::Serialize()
{
  // TODO: Make sure if this causes loss the precision.
  std::stringstream ss;
  ss << "[\"lookat\", \"" << this->targetName << "\", " << this->rad << ", " << this->distance << "]";
  return ss.str();
}
