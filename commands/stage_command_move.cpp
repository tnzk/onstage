#include "stage_command_move.hpp"
#include "thestage.hpp"
#include <sstream>

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
  ISymbol* symbol = stage.GetSymbol(this->targetName);
  symbol->Move(this->dx, this->dy);
}

std::string MoveStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"move\", \"" << this->targetName << "\", " << this->dx << ", " << this->dy << "]";
  return ss.str();
}
