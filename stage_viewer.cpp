#include "stage_viewer.hpp"
#include <sstream>
#include <math.h>
#include <SDL.h>
#include <cairo.h>
#include "stage_command.hpp"
#include "stage_command_shut.hpp"
#include "stage_command_left_hand.hpp"
#include "stage_command_right_hand.hpp"
#include "stage_command_sync.hpp"

void StageViewer::DrawLoadMenu(cairo_t* cairo, double x, double y)
{
  cairo_set_source_rgba(cairo, 0.2, 0.5, 0.8, 0.6);
  cairo_rectangle(cairo, x, y, 300, this->thestage->GetResolutionHeight());
  cairo_fill(cairo);

  std::list<ISymbol*> symbols = this->thestage->GetAllSymbols();
  for (auto sym : symbols) {
    std::cout << sym->instanceId << std::endl;
  }
}

void StageViewer::DrawMetaInfo(cairo_t* cairo, double x, double y)
{
  std::stringstream ss;
  ss << "FPS: " << this->averageFps;
  std::string fps = ss.str();

  ss.str("");
  ss << "Mode: " << UserControlState::StateToString(this->controlContext->controlState->GetState());
  std::string globalMode = ss.str();

  ss.str("");
  ss << "Current: " << this->thestage->GetCurrentFrame();
  std::string currentFrame = ss.str();

  cairo_set_source_rgba(cairo, 0.8, 0.5, 0.5, 0.6);
  cairo_rectangle(cairo, x, y, 200, 200);
  cairo_fill(cairo);
  cairo_set_source_rgba(cairo, 1, 1, 1, 1); 

  cairo_set_font_size(cairo, 17);
  cairo_move_to(cairo, x + 20, y + 30);
  cairo_show_text(cairo, "Meta info");

  cairo_set_font_size(cairo, 12);
  cairo_move_to(cairo, x + 20, y + 60);
  cairo_show_text(cairo, fps.c_str());
  cairo_move_to(cairo, x + 20, y + 80);
  cairo_show_text(cairo, globalMode.c_str());
  cairo_move_to(cairo, x + 20, y + 110);
  cairo_show_text(cairo, currentFrame.c_str());
}

void StageViewer::DrawGlobalMenu(cairo_t* cairo, double x, double y)
{
  cairo_set_source_rgba(cairo, 0.1, 0.1, 0.1, 0.5); 
  cairo_rectangle(cairo, x, y, 200, this->thestage->GetResolutionHeight());
  cairo_fill(cairo);
  cairo_set_source_rgba(cairo, 0.8, 0.3, 0.3, 0.3); 
  cairo_rectangle(cairo, x, y + 58 + 30 * this->controlContext->controlState->index, 200, 30);
  cairo_fill(cairo);
  cairo_set_source_rgba(cairo, 1, 1, 1, 1); 
  cairo_set_font_size(cairo, 22);
  cairo_select_font_face(cairo, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_move_to(cairo, x + 20, y + 50);
  cairo_show_text(cairo, "Mode");
  cairo_move_to(cairo, x + 30, y + 80);
  cairo_show_text(cairo, "Load");
  cairo_move_to(cairo, x + 30, y + 110);
  cairo_show_text(cairo, "Camera");
  cairo_move_to(cairo, x + 30, y + 140);
  cairo_show_text(cairo, "Act");
  cairo_move_to(cairo, x + 30, y + 170);
  cairo_show_text(cairo, "Cancel");
}

void StageViewer::UpdateSurfaceViaCairo(cairo_t* cairo)
{

  UserControlContext* context = this->controlContext;
  auto commands = context->ProcessInput();
  if (commands.size() > 0) {
    this->thestage->SyncForRecording(this->thestage->GetCurrentFrame());
    for (auto command : commands) {
      this->thestage->Execute(*command);
    }
  }

  cairo_set_source_rgb(cairo, 1, 1, 1);
  cairo_paint(cairo);

  // Draw the rendered image.
  this->thestage->ExecuteCommandsUntilCurrentFrame();
  cairo_surface_t* surface = this->thestage->Render();
  cairo_set_source_surface(cairo, surface, 0, 0);
  cairo_paint(cairo);
  cairo_surface_destroy(surface);

  // Draw controls.
  UserControlState::State state = context->controlState->GetState();
  if (state == UserControlState::State::Global) {
    this->DrawGlobalMenu(cairo, 0, 0);
  }

  if (state == UserControlState::State::Loader) {
    this->DrawLoadMenu(cairo, 0, 0);
  }
  this->DrawMetaInfo(cairo, 400, 0);
}

StageViewer::StageViewer(TheStage* stage)
{
  this->thestage = stage;
  this->averageFps = 0;
}

void StageViewer::Run()
{
  this->controlContext = new UserControlContext("/dev/input/js0", this->thestage); // TODO: device name?

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface* sdlsurf;
  SDL_Window* win = SDL_CreateWindow("eveyrthing", 100, 100,
				     this->thestage->GetResolutionWidth(),
				     this->thestage->GetResolutionHeight(), SDL_WINDOW_SHOWN);
  sdlsurf = SDL_GetWindowSurface(win);
  cairo_surface_t *cairosurf = cairo_image_surface_create_for_data ( reinterpret_cast<unsigned char*>(sdlsurf->pixels),
								     CAIRO_FORMAT_RGB24,
								     sdlsurf->w, sdlsurf->h, sdlsurf->pitch);
  cairo_t* cairo = cairo_create(cairosurf);
  SDL_Event event;
  bool quit = false;
  const double frameInterval = 1000.0 / 30.0;
  Uint32 previousTick = SDL_GetTicks() - frameInterval;
  Uint32 tick = SDL_GetTicks();
  Uint32 startedAt = tick;
  
  while (!quit) {
    tick = SDL_GetTicks();
    Uint32 timePassed = tick - startedAt;

    // Process SDL events.
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
	quit = true;
      }
    }

    int correctFrame = floor(timePassed / frameInterval);
    int currentFrame = this->thestage->GetCurrentFrame();
    if (currentFrame != correctFrame) {
      if (currentFrame > correctFrame) { // Too fast.
	// TODO: Do something.
      } else { // currentFrame < correctFrame; Too late.
	for (int i = 0; i < (currentFrame - correctFrame); ++i) {
	  this->thestage->Skip();
	}
	this->UpdateSurfaceViaCairo(cairo);
 	previousTick = tick;
 	// SDL_Delay(tick - previousTick);
      }
      SDL_UpdateWindowSurface(win);
    }
    this->averageFps = currentFrame / (timePassed / 1000.0);
  }
  SDL_Quit();
}
