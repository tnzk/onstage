#include "stage_command_camera_zoom.hpp"
#include "camera.hpp"

CameraZoomStageCommand::CameraZoomStageCommand(double zoom)
{
  this->zoom = zoom;
}

CameraZoomStageCommand::~CameraZoomStageCommand()
{
}

bool CameraZoomStageCommand::Execute(TheStage& stage)
{
  Camera* camera = stage.GetPrimaryCamera();
  camera->SetZoom(this->zoom);
}
