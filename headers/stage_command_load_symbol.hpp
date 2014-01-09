#include <string>
#include "thestage.hpp"

class LoadSymbolStageCommand : public IStageCommand
{
public:
  LoadSymbolStageCommand(std::string);
  ~LoadSymbolStageCommand();
  virtual bool Execute(TheStage&);
private:
  std::string symbolName;
};
