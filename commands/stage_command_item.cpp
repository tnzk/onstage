#include "stage_command_item.hpp"
#include "item.hpp"

ItemStageCommand::ItemStageCommand(std::string name)
{
  this->itemName = name;
}

ItemStageCommand::~ItemStageCommand()
{
}

bool ItemStageCommand::Execute(TheStage& stage)
{
  std::cout << this->itemName << " appeared on the stage." << std::endl;
  Item item(this->itemName);
  
}
