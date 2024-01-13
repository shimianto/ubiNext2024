#include "stdafx.h"
#include "InputHandler.h"
#include <App/app.h>
#include "../Graphics3D/Camera/Camera.h"

void InputHandler::Init()
{
}

void InputHandler::HandleInput (float deltaTime)
{
  if (App::GetController().GetLeftThumbStickY() > 0.5f) {
	Camera::mainCamera.pos.z += 1 / deltaTime;
  } else if (App::GetController().GetLeftThumbStickY() < -0.5f) {
	Camera::mainCamera.pos.z -= 1 / deltaTime;
  }

  if (App::GetController().GetLeftThumbStickX() > 0.5f) {
	Camera::mainCamera.fYaw += 1 / deltaTime;
  } else if (App::GetController().GetLeftThumbStickX() < -0.5f) {
	Camera::mainCamera.fYaw -= 1 / deltaTime;
  }

  if (App::GetController().CheckButton (XINPUT_GAMEPAD_DPAD_UP, false)) {
	Camera::mainCamera.pos.y += 1 / deltaTime;
  }
  if (App::GetController().CheckButton (XINPUT_GAMEPAD_DPAD_DOWN, false)) {
	Camera::mainCamera.pos.y -= 1 / deltaTime;
  }
  if (App::GetController().CheckButton (XINPUT_GAMEPAD_DPAD_LEFT, false)) {
	Camera::mainCamera.pos.x += 1 / deltaTime;
  }
  if (App::GetController().CheckButton (XINPUT_GAMEPAD_DPAD_RIGHT, false)) {
	Camera::mainCamera.pos.x -= 1 / deltaTime;
  }
}
