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
  globalStage->ExecuteCommandsUntilCurrentFrame();  
  cairo_surface_t* surface = globalStage->Render();
  cairo_set_source_surface(cairo, surface, 0, 0);
  cairo_paint(cairo);
  cairo_surface_destroy(surface);
  return TRUE;
}

static gboolean UpdateFrame(GtkWidget* widget)
{
  globalViewer->joystick->ProcessEvent();
  std::pair<int, int> leftAxis = globalViewer->joystick->GetAxis(JoystickState::AxisSymbol::LX, JoystickState::AxisSymbol::LY);
  if (leftAxis.first != 0 || leftAxis.second != 0) {
    globalStage->SyncForRecording(globalStage->GetCurrentFrame());

    double dx = leftAxis.first / 32767.0;
    double dy = leftAxis.second / -32767.0;
    double theta = atan2(dy, dx);
    double r = sqrt(dx * dx + dy * dy) * 150;
    IStageCommand* command = new LeftHandStageCommand("momo.json", theta, r);
    globalStage->Execute(*command);
  }

  std::pair<int, int> rAxis = globalViewer->joystick->GetAxis(JoystickState::AxisSymbol::RX, JoystickState::AxisSymbol::RY);
  if (rAxis.first != 0 || rAxis.second != 0) {
    globalStage->SyncForRecording(globalStage->GetCurrentFrame());

    double dx = rAxis.first / 32767.0;
    double dy = rAxis.second / -32767.0;
    double theta = atan2(dy, dx);
    double r = sqrt(dx * dx + dy * dy) * 150;
    IStageCommand* command = new RightHandStageCommand("momo.json", theta, r);
    globalStage->Execute(*command);
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
  this->joystick = new JoystickState("/dev/input/js0"); // TODO: device name?
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
