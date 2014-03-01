#include "stage_command_camera_move.hpp"
#include "camera.hpp"
#include <sstream>

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

std::string CameraMoveStageCommand::Serialize()
{
  std::stringstream ss;
  ss << "[\"camera_move\", " << this->dx << ", " << this->dy << "]";
  return ss.str();
}
