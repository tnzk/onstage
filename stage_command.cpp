#include "stage_command.hpp"
#include "command_inclusion.hpp"
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>

IStageCommand* StageCommandFactory::Create(picojson::value& jsonCommand)
{
  static bool initialized = false;
  static std::map<std::string, std::function<IStageCommand*(picojson::array&)> > stageCommandFactoryMap;

  if(!initialized) {
    initialized = true;

    stageCommandFactoryMap.insert(std::make_pair("sync", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new SyncStageCommand(command[1].get<double>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("load_actor", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new LoadActorStageCommand(command[1].get<std::string>(), command[2].get<std::string>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("load_symbol", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new LoadSymbolStageCommand(command[1].get<std::string>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("scale", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new ScaleStageCommand(command[1].get<std::string>(), command[2].get<double>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("camera_zoom", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new CameraZoomStageCommand(command[1].get<double>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("camera_move", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new CameraMoveStageCommand(command[1].get<double>(), command[2].get<double>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("move", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new MoveStageCommand(command[1].get<std::string>(), command[2].get<double>(), command[3].get<double>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("speak", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new SpeakStageCommand(command[1].get<std::string>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("shut", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new ShutStageCommand(command[1].get<std::string>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("lookat", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new LookatStageCommand(command[1].get<std::string>(), command[2].get<double>(), command[3].get<double>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("left_hand", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new LeftHandStageCommand(command[1].get<std::string>(), command[2].get<double>(), command[3].get<double>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("eyeblows", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new EyeblowsStageCommand(command[1].get<std::string>(), command[2].get<double>(), command[3].get<double>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("right_hand", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new RightHandStageCommand(
	command[1].get<std::string>(), command[2].get<double>(), command[3].get<double>()
	);
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("facial", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new FacialStageCommand(command[1].get<std::string>(), command[2].get<std::string>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("walk", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new WalkStageCommand(
      command[1].get<std::string>(), command[2].get<double>(), command[3].get<double>());
      return cmd;
    }));
    stageCommandFactoryMap.insert(std::make_pair("stop", [](picojson::array& command) -> IStageCommand* {
      IStageCommand* cmd = new StopStageCommand(
      command[1].get<std::string>()
      );
      return cmd;
    }));
  }
    
  picojson::array& command = jsonCommand.get<picojson::array>();
  std::string commandName = command[0].get<std::string>();

  // Return NullStageCommand if the unknown command requested
  if(stageCommandFactoryMap.find(commandName) != stageCommandFactoryMap.end()) {
    auto f = stageCommandFactoryMap[commandName];
    return f(command);
  } else {
    IStageCommand* cmd = new NullStageCommand(commandName, jsonCommand.serialize());
    return cmd;
  }
}
