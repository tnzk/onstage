#include "thestage.hpp"

bool TheStage::Execute(IStageCommand& command) const
{
  command.Execute();
  return true;
}

bool TheStage::Render(unsigned char*)
{
  return true;
}

bool TheStage::Skip()
{
  return true;
}

