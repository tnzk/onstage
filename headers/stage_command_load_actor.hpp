#include <string>
#include "thestage.hpp"

class LoadActorStageCommand : public IStageCommand
{
private:
  std::string instanceId;
  std::string symbolPath;
public:
  LoadActorStageCommand(std::string id, std::string path);
  ~LoadActorStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
};
