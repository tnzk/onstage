#include "stage_command_sync.hpp"
#include "thestage.hpp"

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
  stage.skipUntil = this->sync_at;
}
