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
#include <librsvg/rsvg.h>
#include <librsvg/rsvg-cairo.h>


int main(int argc, char** argv)
{

  TheStage stage;
  bool isInteractive = false;

  cmdline::parser opt;
  opt.add<std::string>("file", 'f', "Script file.", false);
  opt.add("interactive", 'i', "Run in interactive mode.");
  opt.add("list-commands", 'l', "List all the avaiable commands.");
  opt.parse_check(argc, argv);

  if (opt.exist("list-commands")) {
    std::cout << "Commands supported:" << std::endl;
    exit(0);
  }

  if (opt.exist("interactive")) {
    std::cout << "Interactive mode not supported." << std::endl;
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

  for(picojson::array::iterator it = commands.begin(); it != commands.end(); ++it) {
    stage.storedCommands.push_back(StageCommandFactory::Create(*it));
  }

  stage.Start();
  for(int i = 0; i < stage.GetDuration(); i++) {
    stage.ExecuteCommandsUntilCurrentFrame();
    cairo_surface_t* surface = stage.Render();
    std::stringstream filename;
    filename << outputDirectory << "f" << std::setw(3) << std::setfill('0') << i + 1 << ".png";
    cairo_surface_write_to_png(surface, filename.str().c_str());
    cairo_surface_destroy(surface);
  }
  stage.End();

  rsvg_term();
  return 0;
}

