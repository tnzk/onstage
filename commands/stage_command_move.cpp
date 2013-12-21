#include "stage_command_move.hpp"
#include "thestage.hpp"

MoveStageCommand::MoveStageCommand(std::string targetName, double dx, double dy)
{
  this->targetName = targetName;
  this->dx = dx;
  this->dy = dy;
}

MoveStageCommand::~MoveStageCommand()
{
}

bool MoveStageCommand::Execute(TheStage& stage)
{
  IActable* actable = stage.GetActable(this->targetName);
  actable->Move(this->dx, this->dy);
}
