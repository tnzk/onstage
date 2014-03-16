#include "stage_viewer.hpp"
#include <math.h>
#include <SDL.h>
#include <cairo.h>
#include "stage_command.hpp"
#include "stage_command_shut.hpp"
#include "stage_command_left_hand.hpp"
#include "stage_command_right_hand.hpp"
#include "stage_command_sync.hpp"

#include <math.h>

// TODO: whole of this looks totally disaster. Try gtkmm.
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

  // Draw the rendered image.
  this->thestage->ExecuteCommandsUntilCurrentFrame();
  cairo_surface_t* surface = this->thestage->Render();
  cairo_set_source_surface(cairo, surface, 0, 0);
  cairo_paint(cairo);
  cairo_surface_destroy(surface);

  // Draw controls.
  UserControlState::State state = context->controlState->GetState();
  if (state == UserControlState::State::Global) {
    cairo_set_source_rgba(cairo, 0.1, 0.1, 0.1, 0.5); 
    cairo_rectangle(cairo, 0, 0, 200, this->thestage->GetResolutionHeight());
    cairo_fill(cairo);
    cairo_set_source_rgba(cairo, 0.8, 0.3, 0.3, 0.3); 
    cairo_rectangle(cairo, 0, 58 + 30 * context->controlState->index, 200, 30);
    cairo_fill(cairo);
    cairo_set_source_rgba(cairo, 1, 1, 1, 1); 
    cairo_set_font_size(cairo, 22);
    cairo_select_font_face(cairo, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_move_to(cairo, 20, 50);
    cairo_show_text(cairo, "Mode");
    cairo_move_to(cairo, 30, 80);
    cairo_show_text(cairo, "Load");
    cairo_move_to(cairo, 30, 110);
    cairo_show_text(cairo, "Camera");
    cairo_move_to(cairo, 30, 140);
    cairo_show_text(cairo, "Act");
    cairo_move_to(cairo, 30, 170);
    cairo_show_text(cairo, "Cancel");
  }
    // UserControlState::StateToString(context->controlState->GetState()).c_str()
}

StageViewer::StageViewer(TheStage* stage)
{
  this->thestage = stage;
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
    if (currentFrame != correctFrame) { // Too fast.
      if (currentFrame > correctFrame) {
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
      
  }
  SDL_Quit();
}
