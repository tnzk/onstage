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

bool MoveStageCommand::Execute(TheStage& stage)
{
  std::cout << "I'm here" << std::endl;
}

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

SyncStageCommand::SyncStageCommand(int frame)
{
  this->sync_at = frame;
}

SyncStageCommand::~SyncStageCommand()
{
}

bool SyncStageCommand::Execute(TheStage& stage)
{
  std::cout << "Sync at " << this->sync_at << std::endl;
}

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
