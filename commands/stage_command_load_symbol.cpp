#include "stage_command_load_symbol.hpp"
#include "symbol.hpp"
#include <sstream>

LoadSymbolStageCommand::LoadSymbolStageCommand(std::string name)
{
  this->symbolName = name;
}

LoadSymbolStageCommand::~LoadSymbolStageCommand()
{
}

bool LoadSymbolStageCommand::Execute(TheStage& stage)
{
  std::cout << this->symbolName << " appeared on the stage." << std::endl;
  Symbol* symbol = new Symbol(this->symbolName);
  stage.RegisterSymbol(this->symbolName, symbol);
}

std::string LoadSymbolStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"load_symbol\", \"" << this->symbolName << "\"]";
  return ss.str();
}
