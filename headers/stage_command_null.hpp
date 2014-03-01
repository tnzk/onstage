#include "thestage.hpp"

class NullStageCommand : public IStageCommand
{
private:
  std::string originalName;
  std::string originalCommand;
public:
  NullStageCommand(std::string originalName, std::string originalCommand);
  ~NullStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
};

