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
  UserControlContext* controlContext;
  TheStage* thestage;
};

#endif
