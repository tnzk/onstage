#ifndef THESTAGE_HEADER
#define THESTAGE_HEADER

#include <cairo.h>
#include <map>
#include <list>
#include <string>
#include <sstream>
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
  void Start();
  void End();
  void SetResolution(int, int);
  int GetResolutionWidth();
  int GetResolutionHeight();
  void SetFps(int);
  void SetDuration(int);
  void SetOutputDirectory(std::string);
  void SetResourcesDirectory(std::string);
  int GetDuration();
  int GetCurrentFrame();
  bool Execute(IStageCommand& command);
  cairo_surface_t* Render();
  bool Skip();
  void ShowVideoSetting();
  void RegisterActor(std::string, Actor*);
  void RegisterSymbol(std::string, ISymbol*);
  ISymbol* GetSymbol(std::string name);
  Actor* GetActor(std::string name);
  std::list<ISymbol*> GetAllSymbols();
  Camera* GetPrimaryCamera();
  int AddCamera(double x, double y, double zoom);
  void ExecuteCommandsUntilCurrentFrame();
  void SyncForRecording(int);
  int skipUntil;
  std::list<IStageCommand*> storedCommands;
  std::string GetRecordedScript();
private:
  int width;
  int height;
  int currentFrame;
  int fps;
  int duration; // in frame
  std::list<ISymbol*> symbols;
  int primaryCameraId;
  std::vector<Camera*> cameras;
  std::list<IStageCommand*>::iterator storedCommandIterator;
  std::vector<std::string> recordedCommands;
  std::string resourcesDirectory;
  std::string outputDirectory;
};

#endif

