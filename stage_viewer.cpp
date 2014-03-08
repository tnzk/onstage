#include "stage_viewer.hpp"
#include <gtk/gtk.h>
#include <cairo.h>
#include "stage_command.hpp"
#include "stage_command_shut.hpp"
#include "stage_command_left_hand.hpp"
#include "stage_command_right_hand.hpp"
#include "stage_command_sync.hpp"

#include <math.h>

// TODO: whole of this looks totally disaster. Try gtkmm.
StageViewer* globalViewer;
TheStage* globalStage;

static gboolean OnDrawing(GtkWidget* widget, cairo_t* cairo, gpointer userData)
{
  // Draw the rendered image.
  globalStage->ExecuteCommandsUntilCurrentFrame();
  cairo_surface_t* surface = globalStage->Render();
  cairo_set_source_surface(cairo, surface, 0, 0);
  cairo_paint(cairo);
  cairo_surface_destroy(surface);

  // Draw controls.
  UserControlContext* context = globalViewer->controlContext;
  UserControlState::State state = context->controlState->GetState();
  if (state == UserControlState::State::Global) {
    cairo_set_source_rgba(cairo, 0.1, 0.1, 0.1, 0.5); 
    cairo_rectangle(cairo, 0, 0, 200, globalStage->GetResolutionHeight());
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
  return TRUE;
}

static gboolean UpdateFrame(GtkWidget* widget)
{
  UserControlContext* context = globalViewer->controlContext;
  auto commands = context->ProcessInput();
  if (commands.size() > 0) {
    globalStage->SyncForRecording(globalStage->GetCurrentFrame());
    for (auto command : commands) {
      globalStage->Execute(*command);
    }
  }

  gtk_widget_queue_draw(widget);

  g_timeout_add(33.333, (GSourceFunc)UpdateFrame, (gpointer)widget);
  return FALSE;
}

StageViewer::StageViewer(TheStage* stage)
{
  this->thestage = stage;
}

void StageViewer::Run()
{
  this->controlContext = new UserControlContext("/dev/input/js0"); // TODO: device name?
  globalViewer = this;
  globalStage = this->thestage;
  gtk_init(0, NULL);
  GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget* drawingArea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), drawingArea);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), this->thestage->GetResolutionWidth(), this->thestage->GetResolutionHeight()); 
  g_signal_connect(G_OBJECT(drawingArea), "draw", G_CALLBACK(OnDrawing), NULL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_timeout_add(33.333, (GSourceFunc)UpdateFrame, (gpointer)drawingArea);
  gtk_widget_set_events(drawingArea, gtk_widget_get_events(drawingArea) | GDK_BUTTON_PRESS_MASK);
  gtk_widget_show_all(window);
  gtk_main();
}
