#include "stage_command.hpp"
#include "thestage.hpp"
#include <iostream>
#include <cinttypes>

int main()
{
  auto a = 10;

  std::cout << a << std::endl;

  MoveStageCommand moving;
  IStageCommand* command = &moving;
  command->Execute();

  return 0;
}
