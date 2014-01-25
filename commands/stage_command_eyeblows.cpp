#include "stage_command_eyeblows.hpp"
#include "thestage.hpp"

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
