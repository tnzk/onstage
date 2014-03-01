#include <string>
#include "thestage.hpp"

class SpeakStageCommand : public IStageCommand
{
public:
  SpeakStageCommand(std::string);
  ~SpeakStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  std::string targetName;
};
