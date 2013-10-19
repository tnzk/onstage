#include <cairo.h>
#include <string>

enum ActorFace 
{
  Smily,
  Anger,
  Sad
};

class Actor
{
public:
  Actor(std::string);
  ~Actor();
  bool Render(cairo_t*);
  bool Walk(double x, double y);
  bool LookAt(double r, double distance);
  bool Eyeblows(double r);
  bool Hand(double left_r,  double left_distance, 
            double right_r, double right_distance);
  bool Speak();
  bool Shut();
private:
  int id;
  std::string name;
  int x;
  int y;
  int innerCount;
  bool isSpeaking;
  bool isWalking;
};
