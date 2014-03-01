#include <string>
#include "thestage.hpp"

class CameraMoveStageCommand : public IStageCommand
{
public:
  CameraMoveStageCommand(double, double);
  ~CameraMoveStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  double dx;
  double dy;
};
