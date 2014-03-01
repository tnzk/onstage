
#include "stage_command_right_hand.hpp"
#include "thestage.hpp"
#include <sstream>

RightHandStageCommand::RightHandStageCommand(std::string param0, double param1, double param2)
{
  this->actorId = param0;
  this->rad = param1;
  this->distance = param2;
}

RightHandStageCommand::~RightHandStageCommand()
{
}

bool RightHandStageCommand::Execute(TheStage& stage)
{
  Actor* actor = dynamic_cast<Actor*>(stage.GetSymbol(this->actorId));
  actor->RightHand(this->rad, this->distance);
}

std::string RightHandStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"right_hand\", " << this->rad << ", " << this->distance << "]";
  return ss.str();
}
