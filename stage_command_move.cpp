#include "stage_command_move.hpp"
#include "thestage.hpp"

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
