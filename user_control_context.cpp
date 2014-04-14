#include "user_control_context.hpp"
#include <sstream>
#include "stage_command.hpp"
#include "stage_command_speak.hpp"
#include "stage_command_shut.hpp"
#include "stage_command_left_hand.hpp"
#include "stage_command_right_hand.hpp"
#include "stage_command_camera_zoom.hpp"
#include "stage_command_camera_move.hpp"
#include "stage_command_facial.hpp"
#include "stage_command_lookat.hpp"
#include "stage_command_look_reset.hpp"
#include "stage_command_move.hpp"
#include <iostream>

UserControlContext::UserControlContext(std::string deviceName, TheStage* stage)
{
  this->joystick = new JoystickState(deviceName);
  this->controlState = new UserControlState();
  this->stage = stage;
  this->ChangeTargetActor("test-target");
}

UserControlContext::~UserControlContext() {}

std::vector<IStageCommand*> UserControlContext::ProcessInput() 
{
  std::vector<IStageCommand*> commands;
  auto events = this->joystick->ProcessEvent();
  for (auto ev : events) {
    this->controlState->Input(*this->joystick, ev);
    
    switch (this->controlState->GetState()) {
    case UserControlState::State::Selector:
      {
	this->controlState->min = 0;
	this->controlState->max = this->stage->GetAllSymbols().size() - 1;

	// Ahm...aweful.
	// This should be done by UserControlState somehow.
	if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::A, true)) {
	  auto symbols = this->stage->GetAllSymbols();
	  int count = 0;
	  for (auto sym : symbols) {
	    if (count == this->controlState->index) {
	      this->ChangeTargetActor(sym->instanceId);
	    }
	    count++;
	  }
	  // this->controlState->ChangeStateTo(UserControlState::State::Global);
	  // this->controlState->index = 0;
	}
      }
      break;
    case UserControlState::State::Facial:
      if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::Y, true)) {
	IStageCommand* command = new FacialStageCommand(this->targetId, "anger");
	commands.push_back(command);
      }
      if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::A, true)) {
	IStageCommand* command = new FacialStageCommand(this->targetId, "sad");
	commands.push_back(command);
      }
      if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::X, true)) {
	IStageCommand* command = new FacialStageCommand(this->targetId, "smile");
	commands.push_back(command);
      }
      if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::Y, true)) {
	IStageCommand* command = new FacialStageCommand(this->targetId, "offensive");
	commands.push_back(command);
      }
      if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::R1, true)) {
	IStageCommand* command = new SpeakStageCommand(this->targetId);
	commands.push_back(command);
      }
      if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::R1, false)) {
	IStageCommand* command = new ShutStageCommand(this->targetId);
	commands.push_back(command);
      }
      if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::R2, false)) {
	IStageCommand* command = new LookResetStageCommand(this->targetId);
	commands.push_back(command);
      }
      break;
    case UserControlState::State::Behaviour:
      if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::R1, true)) {
	IStageCommand* command = new SpeakStageCommand(this->targetId);
	commands.push_back(command);
      }
      if (this->joystick->Prove(ev, JoystickState::ButtonSymbol::R1, false)) {
	IStageCommand* command = new ShutStageCommand(this->targetId);
	commands.push_back(command);
      }
      break;
    }
  }

  // Axis matter.
  switch (this->controlState->GetState()) {
  case UserControlState::State::Behaviour:
    {
      auto leftAxis = this->joystick->GetAxis(JoystickState::AxisSymbol::LX, 
					      JoystickState::AxisSymbol::LY);
      if (leftAxis.first != 0 || leftAxis.second != 0) {
	// TODO: Utilize this.
	double dx = leftAxis.first / 32767.0;
	double dy = leftAxis.second / -32767.0;
	double theta = atan2(dy, dx);
	double r = sqrt(dx * dx + dy * dy) * 150;
	IStageCommand* command = new LeftHandStageCommand(this->targetId, theta, r);
	commands.push_back(command);
      }

      auto rightAxis = this->joystick->GetAxis(JoystickState::AxisSymbol::RX, 
					       JoystickState::AxisSymbol::RY);
      if (rightAxis.first != 0 || rightAxis.second != 0) {
	// TODO: Utilize this.
	double dx = rightAxis.first / 32767.0;
	double dy = rightAxis.second / -32767.0;
	double theta = atan2(dy, dx);
	double r = sqrt(dx * dx + dy * dy) * 150;
	IStageCommand* command = new RightHandStageCommand(this->targetId, theta, r);
	commands.push_back(command);
      }

      auto cAxis = this->joystick->GetAxis(JoystickState::AxisSymbol::CX, 
                                           JoystickState::AxisSymbol::CY);
      if (cAxis.first != 0 || cAxis.second != 0) {
	// TODO: Utilize this.
	double dx = (cAxis.first / 32767.0) * 10.0;
	double dy = (cAxis.second / -32767.0) * -10.0;
	IStageCommand* command = new MoveStageCommand(this->targetId, dx, dy);
	commands.push_back(command);
      }

    }
    break;
  case UserControlState::State::Facial:
    {
      auto rightAxis = this->joystick->GetAxis(JoystickState::AxisSymbol::RX, 
					       JoystickState::AxisSymbol::RY);
      if (rightAxis.first != 0 || rightAxis.second != 0) {
	// TODO: Utilize this.
	double dx = rightAxis.first / 32767.0;
	double dy = rightAxis.second / -32767.0;
	double theta = atan2(dy, dx);
	double r = sqrt(dx * dx + dy * dy) * 150;
	IStageCommand* command = new LookatStageCommand(this->targetId, theta, r);
	commands.push_back(command);
      }
    }
    break;
  case UserControlState::State::Camera:
    {
      Camera* camera = this->stage->GetPrimaryCamera();
      int zoomSlider = this->joystick->GetAxis(JoystickState::AxisSymbol::LY);
      if (zoomSlider != 0) {
	double zoom = zoomSlider / 327670.0; // TODO: Don't be magical.
	IStageCommand* command = new CameraZoomStageCommand(camera->GetZoom() - zoom);
	commands.push_back(command);
      }

      auto rightAxis = this->joystick->GetAxis(JoystickState::AxisSymbol::RX, JoystickState::AxisSymbol::RY);
      if (rightAxis.first != 0 || rightAxis.second != 0) {
	double x;
	double y;
	camera->GetPosition(x, y);
	x += (rightAxis.first / 32767.0) * 10.0; // TODO: Don't be magical.
	y += (rightAxis.second / 32767.0) * 10.0; // TODO: Don't be magical.
	IStageCommand* command = new CameraMoveStageCommand(x, y);
	commands.push_back(command);
      }

    }
    break;
  }
  
  return commands;
}

std::string UserControlContext::ToString()
{
  std::string stateString = UserControlState::StateToString(this->controlState->GetState());

  std::stringstream ss;
  ss << "State: " << stateString;
  return ss.str();
}

void UserControlContext::ChangeTargetActor(std::string actorId)
{
  this->targetId = actorId;
}

std::string UserControlContext::GetTargetActor()
{
  return this->targetId;
}
