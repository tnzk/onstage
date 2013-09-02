#include "stage_command.hpp"
#include "thestage.hpp"
#include "picojson.h"
#include <iostream>
#include <string>
#include <cinttypes>

int main()
{

  TheStage stage;

  picojson::value json;
  std::cin >> json;
  picojson::object& obj = json.get<picojson::object>();
  picojson::array& commands = obj["commands"].get<picojson::array>();

  picojson::object& videoSetting = obj["video"].get<picojson::object>();
  stage.SetFps((int)videoSetting["fps"].get<double>());
  stage.SetDuration((int)videoSetting["duration"].get<double>());
  stage.SetResolution((int)videoSetting["width"].get<double>(), (int)videoSetting["height"].get<double>());
  stage.ShowVideoSetting();

  int skipAt = 0;
  picojson::array::iterator it = commands.begin();
  for(int i = 0; i < stage.GetDuration(); i++) {
    for (; stage.GetCurrentFrame() >= stage.skipUntil && it != commands.end(); it++) {
      IStageCommand& command = StageCommandFactory::Create(*it);
      stage.Execute(command);
    }
    stage.Render(NULL);
  }

  return 0;
}
