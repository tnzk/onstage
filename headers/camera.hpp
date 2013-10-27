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
  void SetResolution(double width, double height);
  double GetZoom();
  void Translate(double sx, double sy, double& dx, double& dy); // TODO: theres got to be better name
private:
  double x;
  double y;
  double width;
  double height;
  double zoom;
};

#endif
