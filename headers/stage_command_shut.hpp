#include <string>
#include "thestage.hpp"

class ShutStageCommand : public IStageCommand
{
public:
  ShutStageCommand(std::string);
  ~ShutStageCommand();
  virtual bool Execute(TheStage&);
private:
  std::string actorId;
};
