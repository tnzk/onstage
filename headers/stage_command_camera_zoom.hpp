#include <string>
#include "thestage.hpp"

class CameraZoomStageCommand : public IStageCommand
{
public:
  CameraZoomStageCommand(double);
  ~CameraZoomStageCommand();
  virtual bool Execute(TheStage&);
  virtual std::string Serialize();
private:
  double zoom;
};
