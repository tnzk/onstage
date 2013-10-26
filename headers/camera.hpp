#ifndef CAMERA_HEADER

#define CAMERA_HEADER

class Camera
{
public:
  Camera();
  ~Camera();
  void SetPosition(double x, double y);
  void SetZoom(double z);
  void GetPosiotion(double& x, double& y);
  double GetZoom();
private:
  double x;
  double y;
  double zoom;
};

#endif
