#include "stage_command_scale.hpp"
#include "symbol.hpp"
#include "actor.hpp"
#include <sstream>

ScaleStageCommand::ScaleStageCommand(std::string name, double scale)
{
  this->targetName = name;
  this->scale = scale;
}

ScaleStageCommand::~ScaleStageCommand()
{
}

bool ScaleStageCommand::Execute(TheStage& stage)
{
  ISymbol* symbol = stage.GetSymbol(this->targetName);
  symbol->SetScale(this->scale);
}

std::string ScaleStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"scale\", \"" << this->targetName << "\", " << this->scale << "]";
  return ss.str();
}
