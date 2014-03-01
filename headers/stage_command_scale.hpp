#include <string>
#include "thestage.hpp"

class ScaleStageCommand : public IStageCommand
{
public:
  ScaleStageCommand(std::string, double);
  ~ScaleStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  std::string targetName;
  double scale;
};
