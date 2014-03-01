#include "stage_command_left_hand.hpp"
#include "thestage.hpp"
#include <sstream>

LeftHandStageCommand::LeftHandStageCommand(std::string param0, double param1, double param2)
{
  this->actorId = param0;
  this->rad = param1;
  this->distance = param2;
}

LeftHandStageCommand::~LeftHandStageCommand()
{
}

bool LeftHandStageCommand::Execute(TheStage& stage)
{
  Actor* actor = dynamic_cast<Actor*>(stage.GetSymbol(this->actorId));
  actor->LeftHand(this->rad, this->distance);
}

std::string LeftHandStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"left_hand\", " << this->rad << ", " << this->distance << "]";
  return ss.str();
}
