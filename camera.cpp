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

#include <iostream>
void Camera::Translate(double sx, double sy, double& dx, double& dy)
{
  dx = (sx + (this->x - this->width  / 2 * this->zoom)) ;
  dy = (sy + (this->y - this->height / 2 * this->zoom));
/*
  std::cout << this->zoom << std::endl;
  std::cout << sx << ", " << sy << std::endl;
  std::cout << this->x << ", " << this->y << std::endl;
  std::cout << this->width << ", " << this->height << std::endl;
  std::cout << dx << ", " << dy << std::endl;
// */
}

void Camera::SetResolution(double width, double height)
{
  this->width = width;
  this->height = height;
}
