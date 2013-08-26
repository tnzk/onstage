#include "stage_command.hpp"
#include <map>
#include <algorithm>
#include <functional>
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

NullStageCommand::NullStageCommand()
{
}

NullStageCommand::~NullStageCommand()
{
}

bool NullStageCommand::Execute()
{
}

SyncStageCommand::SyncStageCommand(int frame)
{
  this->sync_at = frame;
}

SyncStageCommand::~SyncStageCommand()
{
}

bool SyncStageCommand::Execute()
{
  std::cout << "Sync at " << this->sync_at << std::endl;
}



IStageCommand& StageCommandFactory::Create(picojson::value& jsonCommand)
{
  static std::map<std::string, std::function<IStageCommand&(picojson::array&)> > stageCommandFactoryMap;
  stageCommandFactoryMap.insert(std::make_pair("sync", [](picojson::array& command) -> IStageCommand& {
    IStageCommand* cmd = new SyncStageCommand(command[1].get<double>());
    return *cmd;
  }));
    
  picojson::array& command = jsonCommand.get<picojson::array>();
  std::string commandName = command[0].get<std::string>();

  if(stageCommandFactoryMap.find(commandName) != stageCommandFactoryMap.end()) {
    auto f = stageCommandFactoryMap[commandName];
    return f(command);
  } else {
    IStageCommand* cmd = new NullStageCommand();
    return *cmd;
  }
}
