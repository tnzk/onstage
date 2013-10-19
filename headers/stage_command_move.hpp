#include "thestage.hpp"

class MoveStageCommand : public IStageCommand
{
private:
public:
  MoveStageCommand();
  ~MoveStageCommand();
  virtual bool Execute(TheStage&);
};
