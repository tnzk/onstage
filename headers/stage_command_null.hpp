#include "thestage.hpp"

class NullStageCommand : public IStageCommand
{
private:
  std::string originalName;
public:
  NullStageCommand(std::string);
  ~NullStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
};

