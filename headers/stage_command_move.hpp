#include <string>
#include "thestage.hpp"

class MoveStageCommand : public IStageCommand
{
public:
  MoveStageCommand(std::string, double, double);
  ~MoveStageCommand();
  virtual bool Execute(TheStage&);
private:
  std::string targetName;
  double dx;
  double dy;
};
