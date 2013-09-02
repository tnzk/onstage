#include "thestage.hpp"

class SyncStageCommand : public IStageCommand
{
private:
  int sync_at;
public:
  SyncStageCommand(int frame);
  ~SyncStageCommand();
  virtual bool Execute(TheStage&);
};

