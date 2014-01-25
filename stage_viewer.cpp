#include "stage_viewer.hpp"
#include <gtk/gtk.h>
#include <cairo.h>

// TODO: whole of this looks totally disaster. Try gtkmm.

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
