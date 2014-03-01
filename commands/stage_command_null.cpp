#include "stage_command_null.hpp"
#include "thestage.hpp"

NullStageCommand::NullStageCommand(std::string originalName, std::string originalCommand)
{
  this->originalName = originalName;
  this->originalCommand = originalCommand;
}

NullStageCommand::~NullStageCommand()
{
}

bool NullStageCommand::Execute(TheStage& stage)
{
  std::cout << "Unknown command issued: " << this->originalName << std::endl;
}

std::string NullStageCommand::Serialize()
{
  return this->originalCommand;
}
