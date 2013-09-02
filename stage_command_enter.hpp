#include <string>
#include "thestage.hpp"

class EnterStageCommand : public IStageCommand
{
private:
  std::string actorName;
public:
  EnterStageCommand(std::string);
  ~EnterStageCommand();
  virtual bool Execute(TheStage&);
};
