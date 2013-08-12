#include "stage_command.hpp"
#include <iostream>


MoveStageCommand::MoveStageCommand()
{
}

MoveStageCommand::~MoveStageCommand()
{
}

bool MoveStageCommand::Execute()
{
  std::cout << "I'm here" << std::endl;
}
