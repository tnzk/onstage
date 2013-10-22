#include "stage_command_scale.hpp"
#include "item.hpp"
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
  std::cout << "Scale command" << std::endl;
}
