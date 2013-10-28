#include "stage_command_camera_move.hpp"
#include "camera.hpp"

CameraMoveStageCommand::CameraMoveStageCommand(double dx, double dy)
{
  this->dx = dx;
  this->dy = dy;
}

CameraMoveStageCommand::~CameraMoveStageCommand()
{
}

bool CameraMoveStageCommand::Execute(TheStage& stage)
{
  Camera* camera = stage.GetPrimaryCamera();
  double x;
  double y;
  //camera->GetPosition(x, y);
  //camera->SetPosition(x + dx, y + dy);
  camera->SetPosition(dx, dy);
}
