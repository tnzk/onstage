#include "stage_command_speak.hpp"
#include "actor.hpp"
#include "thestage.hpp"
#include <sstream>

SpeakStageCommand::SpeakStageCommand(std::string targetName)
{
  this->targetName = targetName;
}

SpeakStageCommand::~SpeakStageCommand()
{
}

bool SpeakStageCommand::Execute(TheStage& stage)
{
  Actor* actor = stage.GetActor(this->targetName);
  actor->Speak();
}

std::string SpeakStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"speak\", \"" << this->targetName << "\"]";
  return ss.str();
}
