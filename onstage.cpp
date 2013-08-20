#include "stage_command.hpp"
#include "thestage.hpp"
#include "picojson.h"
#include <iostream>
#include <string>
#include <cinttypes>

int main()
{

  picojson::value json;
  std::cin >> json;
  picojson::object& obj = json.get<picojson::object>();
  picojson::array& commands = obj["commands"].get<picojson::array>();
  std::cout << commands[2] << std::endl;

  MoveStageCommand moving;
  IStageCommand& command = moving;

  TheStage stage;
  stage.Execute(command);

  return 0;
}
