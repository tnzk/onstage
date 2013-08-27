#include "thestage.hpp"

bool TheStage::Execute(IStageCommand& command) const
{
  TheStage stage = *this;
  command.Execute(stage);
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

