#include "stage_command.hpp"
#include "stage_command_sync.hpp"
#include "stage_command_null.hpp"
#include "stage_command_move.hpp"
#include "stage_command_enter.hpp"
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>

IStageCommand& StageCommandFactory::Create(picojson::value& jsonCommand)
{
  static bool initialized = false;
  static std::map<std::string, std::function<IStageCommand&(picojson::array&)> > stageCommandFactoryMap;

  if(!initialized) {
    initialized = true;

    stageCommandFactoryMap.insert(std::make_pair("sync", [](picojson::array& command) -> IStageCommand& {
      IStageCommand* cmd = new SyncStageCommand(command[1].get<double>());
      return *cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("enter", [](picojson::array& command) -> IStageCommand& {
      IStageCommand* cmd = new EnterStageCommand(command[1].get<std::string>());
      return *cmd;
    }));
  }
    
  picojson::array& command = jsonCommand.get<picojson::array>();
  std::string commandName = command[0].get<std::string>();

  // Return NullStageCommand if the unknown command requested
  if(stageCommandFactoryMap.find(commandName) != stageCommandFactoryMap.end()) {
    auto f = stageCommandFactoryMap[commandName];
    return f(command);
  } else {
    IStageCommand* cmd = new NullStageCommand(commandName);
    return *cmd;
  }
}
