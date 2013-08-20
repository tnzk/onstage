#include "stage_command.hpp"
#include "thestage.hpp"
#include <iostream>
#include <cinttypes>

int main()
{

  MoveStageCommand moving;
  IStageCommand& command = moving;

  TheStage stage;
  stage.Execute(command);

  return 0;
}
