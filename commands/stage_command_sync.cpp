#include "stage_command_sync.hpp"
#include "thestage.hpp"

#include <sstream>

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

std::string SyncStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"sync\", " << this->sync_at << "]";
  return ss.str();
}
