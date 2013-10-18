#include "stage_command.hpp"
#include "thestage.hpp"
#include "picojson.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cinttypes>
#include <cairo.h>

int main()
{

  TheStage stage;

  picojson::value json;
  std::cin >> json;
  picojson::object& obj = json.get<picojson::object>();
  picojson::array& commands = obj["commands"].get<picojson::array>();

  picojson::object& videoSetting = obj["video"].get<picojson::object>();
  std::string outputDirectory = videoSetting["output"].get<std::string>();
  stage.SetFps((int)videoSetting["fps"].get<double>());
  stage.SetDuration((int)videoSetting["duration"].get<double>());
  stage.SetResolution((int)videoSetting["width"].get<double>(), (int)videoSetting["height"].get<double>());
  stage.ShowVideoSetting();

  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, stage.GetResolutionWidth(), stage.GetResolutionHeight());

  int skipAt = 0;
  picojson::array::iterator it = commands.begin();
  for(int i = 0; i < stage.GetDuration(); i++) {
    for (; stage.GetCurrentFrame() >= stage.skipUntil && it != commands.end(); it++) {
      IStageCommand& command = StageCommandFactory::Create(*it);
      stage.Execute(command);
    }
    stage.Render(surface);
    std::stringstream filename;
    filename << outputDirectory << "hello" << std::setw(3) << std::setfill('0') << i << ".png";
    cairo_surface_write_to_png(surface, filename.str().c_str());
  }

  return 0;
}

