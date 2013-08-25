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

IStageCommand& StageCommandFactory::Create(picojson::value& jsonCommand)
{
  picojson::array& command = jsonCommand.get<picojson::array>();
  std::cout << command[0].get<std::string>() << std::endl;
}
