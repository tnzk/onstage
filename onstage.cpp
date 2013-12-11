#include "stage_command.hpp"
#include "thestage.hpp"
#include "picojson.h"
#include "cmdline.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cinttypes>
#include <cairo.h>

int main(int argc, char** argv)
{

  TheStage stage;

  cmdline::parser opt;
  opt.add<std::string>("file", 'f', "Script file.", false);
  opt.add("list-commands", 'l', "List all the avaiable commands.");
  opt.parse_check(argc, argv);

  if (opt.exist("list-commands")) {
    std::cout << "Commands supported:" << std::endl;
    
    exit(0);
  }

  std::string scriptFileName = opt.get<std::string>("file");
  std::ifstream scriptFile(scriptFileName);

  if (!scriptFile.is_open()) {
    std::cout << "No such file: " << scriptFileName << std::endl;
    exit(1);
  }

  picojson::value json;
  scriptFile >> json;
  scriptFile.close();
  picojson::object& obj = json.get<picojson::object>();
  picojson::array& commands = obj["commands"].get<picojson::array>();

  picojson::object& videoSetting = obj["video"].get<picojson::object>();
  std::string outputDirectory = videoSetting["output"].get<std::string>();
  stage.SetFps((int)videoSetting["fps"].get<double>());
  stage.SetDuration((int)videoSetting["duration"].get<double>());
  stage.SetResolution((int)videoSetting["width"].get<double>(), (int)videoSetting["height"].get<double>());
  stage.ShowVideoSetting();

  rsvg_init();
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
    filename << outputDirectory << "f" << std::setw(3) << std::setfill('0') << i + 1 << ".png";
    cairo_surface_write_to_png(surface, filename.str().c_str());
  }

  rsvg_term();
  return 0;
}

