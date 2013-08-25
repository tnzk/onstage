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

  for (picojson::array::iterator it = commands.begin(); it != commands.end(); it++) {
    StageCommandFactory::Create(*it);
  }

  MoveStageCommand moving;
  IStageCommand& command = moving;

  TheStage stage;
  stage.Execute(command);

  return 0;
}
