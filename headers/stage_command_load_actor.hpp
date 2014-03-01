#include <string>
#include "thestage.hpp"

class LoadActorStageCommand : public IStageCommand
{
private:
  std::string actorName;
public:
  LoadActorStageCommand(std::string);
  ~LoadActorStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
};
