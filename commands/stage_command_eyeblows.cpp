#include "stage_command_eyeblows.hpp"
#include "thestage.hpp"
#include <sstream>

EyeblowsStageCommand::EyeblowsStageCommand(std::string targetName, double left, double right)
{
  this->targetName = targetName;
  this->left = left;
  this->right = right;
}

EyeblowsStageCommand::~EyeblowsStageCommand()
{
}

bool EyeblowsStageCommand::Execute(TheStage& stage)
{
  Actor* actor = dynamic_cast<Actor*>(stage.GetSymbol(this->targetName));
  actor->Eyeblows(this->left, this->right);
}

std::string EyeblowsStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"eyeblows\", \"" << this->targetName << "\", " << this->left << ", " << this->right <<"]";
  return ss.str();
}
