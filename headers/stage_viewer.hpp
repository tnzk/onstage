#ifndef STAGE_VIEWER_HEADER
#define STAGE_VIEWER_HEADER

#include "thestage.hpp"
#include "user_control_context.hpp"

class StageViewer
{
public:
  StageViewer(TheStage* const);
  void Run();
private:
  void UpdateSurfaceViaCairo(cairo_t* cairo);
  void DrawGlobalMenu(cairo_t* cairo, double x, double y);
  void DrawMetaInfo(cairo_t* cairo, double x, double y);
  void DrawLoadMenu(cairo_t* cairo, double x, double y);
  UserControlContext* controlContext;
  TheStage* thestage;
  double averageFps;
};

#endif
