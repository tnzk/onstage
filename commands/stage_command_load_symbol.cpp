#include "stage_command_load_symbol.hpp"
#include "symbol.hpp"

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
