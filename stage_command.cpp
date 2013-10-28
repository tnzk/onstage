#include "stage_command.hpp"
#include "stage_command_sync.hpp"
#include "stage_command_null.hpp"
#include "stage_command_move.hpp"
#include "stage_command_enter.hpp"
#include "stage_command_item.hpp"
#include "stage_command_scale.hpp"
#include "stage_command_camera_zoom.hpp"
#include "stage_command_camera_move.hpp"
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
    stageCommandFactoryMap.insert(std::make_pair("item", [](picojson::array& command) -> IStageCommand& {
      IStageCommand* cmd = new ItemStageCommand(command[1].get<std::string>());
      return *cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("scale", [](picojson::array& command) -> IStageCommand& {
      IStageCommand* cmd = new ScaleStageCommand(command[1].get<std::string>(), command[2].get<double>());
      return *cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("camera_zoom", [](picojson::array& command) -> IStageCommand& {
      IStageCommand* cmd = new CameraZoomStageCommand(command[1].get<double>());
      return *cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("camera_move", [](picojson::array& command) -> IStageCommand& {
          IStageCommand* cmd = new CameraMoveStageCommand(command[1].get<double>(), command[2].get<double>());
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
