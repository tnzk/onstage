#include <string>
#include "thestage.hpp"

class ShutStageCommand : public IStageCommand
{
public:
  ShutStageCommand(std::string);
  ~ShutStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  std::string actorId;
};
