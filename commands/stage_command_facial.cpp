#include "stage_command_facial.hpp"
#include <sstream>

FacialStageCommand::FacialStageCommand(std::string name, std::string facial)
{
  this->actorId = name;
  this->facial = facial;
}

FacialStageCommand::~FacialStageCommand()
{
}

bool FacialStageCommand::Execute(TheStage& stage)
{
  Actor* actor = dynamic_cast<Actor*>(stage.GetSymbol(this->actorId));
  actor->ChangeFacial(this->facial);
}

std::string FacialStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"facial\", \"" << this->actorId << "\", \"" << this->facial << "\"]";
  return ss.str();
}
