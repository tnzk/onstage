#include "thestage.hpp"
#include <stdlib.h>
#include <algorithm>

TheStage::TheStage()
{
  this->width = 1280;
  this->height = 720;
  this->currentFrame = 0;
  this->fps = 30;
  this->duration = 150;
  this->skipUntil = 0;
  this->primaryCameraId = this->AddCamera(this->width / 2, this->height / 2, 1);
}

void TheStage::ShowVideoSetting()
{
  std::cout << "== Video setting ====" << std::endl;
  std::cout << "     FPS: " << this->fps << std::endl;
  std::cout << "duration: " << this->duration << " frames("
            << this->duration / this->fps << "s)" << std::endl;
  std::cout << "   width: " << this->width << std::endl;
  std::cout << "  height: " << this->height << std::endl;
}

void TheStage::SetResolution(int width, int height)
{
  this->width = width;
  this->height = height;
}

void TheStage::SetFps(int fps)
{
  if(fps > 0) this->fps = fps;
}

void TheStage::SetDuration(int duration)
{
  this->duration = duration;
}

int TheStage::GetDuration() { return this->duration; }

bool TheStage::Execute(IStageCommand& command) 
{
  command.Execute(*this);
  this->recordingStream << "     " << command.Serialize() << "," << std::endl;
  return true;
}

int TheStage::GetCurrentFrame() { return this->currentFrame; }

cairo_surface_t* TheStage::Render()
{
  this->currentFrame++;

  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, this->width, this->height);
  cairo_t* cairo = cairo_create(surface);

  // Clear the surface
  cairo_set_source_rgb(cairo, 1.0, 1.0, 1.0);
  cairo_paint(cairo);

  for(std::list<ISymbol*>::iterator it = this->symbols.begin(); it != this->symbols.end(); ++it) {
    ISymbol* symbol = *it;
    Camera* primaryCamera = this->GetPrimaryCamera();
    double rx;
    double ry;
    double rscale = primaryCamera->GetZoom();
    symbol->Sync(this->currentFrame);
    primaryCamera->Translate(symbol->x, symbol->y, rx, ry);
    cairo_surface_t* subsurface = symbol->Render(rscale);
    cairo_translate(cairo, rx, ry);
    cairo_rotate(cairo, symbol->angle);
    cairo_translate(cairo, -symbol->centerX * rscale, -symbol->centerY * rscale);
    cairo_set_source_surface(cairo, subsurface, 0, 0);
    cairo_paint(cairo);
    cairo_surface_destroy(subsurface);
    cairo_identity_matrix(cairo);
  }

  cairo_destroy(cairo);
  return surface;
}

bool TheStage::Skip()
{
  std::cout << this->currentFrame << "th frame skipped." << std::endl;
  this->currentFrame++;
  return true;
}

int TheStage::GetResolutionWidth() { return this->width; }
int TheStage::GetResolutionHeight() { return this->height; }

void TheStage::RegisterSymbol(std::string name, ISymbol* symbol)
{
  this->symbols.push_back(symbol);
}

void TheStage::RegisterActor(std::string name, Actor* actor)
{
  this->RegisterSymbol(name, actor);
}

ISymbol* TheStage::GetSymbol(std::string name)
{
  std::list<ISymbol*>::iterator it;
  it = std::find_if(this->symbols.begin(), this->symbols.end(), [name](ISymbol* actable) { return actable->GetName() == name; });
  return it != this->symbols.end() ? *it : NULL;
}

Actor* TheStage::GetActor(std::string name)
{
  // TODO: Make sure to return NULL if the symbol is not an instance of Actor
  return dynamic_cast<Actor*>(this->GetSymbol(name));
}

int TheStage::AddCamera(double x, double y, double zoom)
{
  Camera* camera = new Camera();
  camera->SetPosition(x, y);
  camera->SetZoom(zoom);
  camera->SetResolution(this->width, this->height);
  this->cameras.push_back(camera);
  return this->cameras.size() - 1;
}

Camera* TheStage::GetPrimaryCamera()
{
  return this->cameras[this->primaryCameraId];
}

void TheStage::ExecuteCommandsUntilCurrentFrame()
{
  auto& it = this->storedCommandIterator;
  for (; this->GetCurrentFrame() >= this->skipUntil 
	 && it != this->storedCommands.end(); ++it) {
    IStageCommand* command = *it;
    this->Execute(*command);
  }
}

void TheStage::Start()
{
  this->storedCommandIterator = this->storedCommands.begin();
}

void TheStage::End()
{
  // TODO: release the resouces
}

std::string TheStage::GetRecordedScript()
{
  std::stringstream stageScriptStream;
  stageScriptStream << "{\n"
		    << "  \"video\": {\n"
		    << "    \"fps\": " << this->fps << ",\n"
		    << "    \"duration\": " << this->duration << ",\n"
		    << "    \"width\": " << this->width << ",\n"
		    << "    \"height\": " << this->height << ",\n"
		    << "    \"resources\": " << "\"" << this->resourcesDirectory << "\"" << ",\n"
		    << "    \"output\": " << "\"" << this->outputDirectory << "\"" << "\n"
		    << "  },\n"
		    << "  \"commands\": [\n"
		    << this->recordingStream.str()
		    << "    [\"dammy\"]\n"
		    << "  ]\n"
		    << "}\n";
    return stageScriptStream.str();
}

void TheStage::SetOutputDirectory(std::string path)
{
  this->outputDirectory = path;
}

void TheStage::SetResourcesDirectory(std::string path)
{
  this->resourcesDirectory = path;
}
