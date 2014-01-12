#include <string>
#include "thestage.hpp"

class SpeakStageCommand : public IStageCommand
{
public:
  SpeakStageCommand(std::string);
  ~SpeakStageCommand();
  virtual bool Execute(TheStage&);
private:
  std::string targetName;
};
