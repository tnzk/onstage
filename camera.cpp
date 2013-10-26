#include "camera.hpp"

Camera::Camera()
{
  this->x = 0;
  this->y = 0;
  this->zoom = 1.0;
}

void Camera::SetPosition(double x, double y)
{
  this->x = x;
  this->y = y;
}

void Camera::SetZoom(double z)
{
  this->zoom = z;
}

void Camera::GetPosiotion(double& x, double& y)
{
  x = this->x;
  y = this->y;
}

double Camera::GetZoom()
{
  return this->zoom;
}
