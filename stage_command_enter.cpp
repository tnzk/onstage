#include "stage_command_enter.hpp"

EnterStageCommand::EnterStageCommand(std::string name)
{
  this->actorName = name;
}

EnterStageCommand::~EnterStageCommand()
{
}

bool EnterStageCommand::Execute(TheStage& stage)
{
  std::cout << this->actorName << " enters." << std::endl;
}
