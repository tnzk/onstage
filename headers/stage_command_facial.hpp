#include <string>
#include "thestage.hpp"

class FacialStageCommand : public IStageCommand
{
private:
  std::string actorId;
  std::string facial;
public:
  FacialStageCommand(std::string, std::string);
  ~FacialStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
};
