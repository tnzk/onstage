#include "stage_command_load_symbol.hpp"
#include "symbol.hpp"
#include <sstream>

LoadSymbolStageCommand::LoadSymbolStageCommand(std::string id, std::string path)
{
  this->instanceId = id;
  this->symbolPath = path;
}

LoadSymbolStageCommand::~LoadSymbolStageCommand()
{
}

bool LoadSymbolStageCommand::Execute(TheStage& stage)
{
  std::cout << this->instanceId << " appeared on the stage." << std::endl;
  Symbol* symbol = new Symbol(this->instanceId, this->symbolPath);
  stage.RegisterSymbol(this->instanceId, symbol);
}

std::string LoadSymbolStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"load_symbol\", \"" << this->instanceId << "\", \"" << this->symbolPath <<  "\"]";
  return ss.str();
}
