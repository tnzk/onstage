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
  int current = stage.GetCurrentFrame();
  if (current < this->sync_at) {
    stage.skipUntil = this->sync_at;
    std::cout << "Sync at " << this->sync_at << std::endl;
  } else {
    std::cout << "Invalid sync: Request for " << this->sync_at << " at " << current << std::endl;
  }
  
}

std::string SyncStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"sync\", " << this->sync_at << "]";
  return ss.str();
}
