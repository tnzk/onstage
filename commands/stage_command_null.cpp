#include "stage_command_null.hpp"
#include "thestage.hpp"

NullStageCommand::NullStageCommand(std::string commandName)
{
  this->originalName = commandName;
}

NullStageCommand::~NullStageCommand()
{
}

bool NullStageCommand::Execute(TheStage& stage)
{
  std::cout << "Unknown command issued: " << this->originalName << std::endl;
}

