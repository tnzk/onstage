#ifndef THESTAGE_HEADER
#define THESTAGE_HEADER

#include <cairo.h>
#include <map>
#include <list>
#include <string>
#include "isymbol.hpp"
#include "symbol.hpp"
#include "actor.hpp"
#include "camera.hpp"
#include "stage_command.hpp"

enum StageState
{
  Rendering
};

class TheStage
{
public:
  TheStage();
  void SetResolution(int, int);
  int GetResolutionWidth();
  int GetResolutionHeight();
  void SetFps(int);
  void SetDuration(int);
  int GetDuration();
  int GetCurrentFrame();
  bool Execute(IStageCommand& command);
  bool Render(cairo_surface_t*);
  bool Skip();
  void ShowVideoSetting();
  void RegisterActor(std::string, Actor*);
  void RegisterSymbol(std::string, ISymbol*);
  ISymbol* GetSymbol(std::string name);
  Camera* GetPrimaryCamera();
  int AddCamera(double x, double y, double zoom);
  int skipUntil;
private:
  int width;
  int height;
  int currentFrame;
  int fps;
  int duration; // in frame
  std::list<ISymbol*> symbols;
  int primaryCameraId;
  std::vector<Camera*> cameras;
};

#endif

