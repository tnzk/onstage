#include <string>
#include "thestage.hpp"

class LoadSymbolStageCommand : public IStageCommand
{
public:
  LoadSymbolStageCommand(std::string, std::string);
  ~LoadSymbolStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  std::string instanceId;
  std::string symbolPath;
};
