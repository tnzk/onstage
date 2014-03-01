#include <string>
#include "thestage.hpp"

class LoadSymbolStageCommand : public IStageCommand
{
public:
  LoadSymbolStageCommand(std::string);
  ~LoadSymbolStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  std::string symbolName;
};
