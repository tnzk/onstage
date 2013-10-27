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

void Camera::Translate(double sx, double sy, double& dx, double& dy)
{
  dx = (sx - (this->x - this->width  / 2)) * this->zoom;
  dy = (sy - (this->y - this->height / 2)) * this->zoom;
}

void Camera::SetResolution(double width, double height)
{
  this->width = width;
  this->height = height;
}
