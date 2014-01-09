#include "stage_command_scale.hpp"
#include "symbol.hpp"
#include "actor.hpp"

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
