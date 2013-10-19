#include <string>
#include "thestage.hpp"

class ItemStageCommand : public IStageCommand
{
public:
  ItemStageCommand(std::string);
  ~ItemStageCommand();
  virtual bool Execute(TheStage&);
private:
  std::string itemName;
};
