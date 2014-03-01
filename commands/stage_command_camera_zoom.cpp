#include "stage_command_camera_zoom.hpp"
#include "camera.hpp"
#include <sstream>

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

std::string CameraZoomStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"camera_zoom\", " << this->zoom << "]";
  return ss.str();
}
