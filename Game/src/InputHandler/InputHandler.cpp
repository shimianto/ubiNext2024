#include "stdafx.h"
#include "InputHandler.h"
#include <App/app.h>
#include "../Graphics3D/Camera/Camera.h"
#include "../Scene/Scene.h"

void InputHandler::Init (Scene &scene)
{
  m_Scene = &scene;
}

void InputHandler::HandleInput (float deltaTime)
{
  switch (m_Scene->GetScreen()) {
  case MENU_SCREEN:
	  HandleMenuSceneInput (deltaTime);
	break;
  case MAIN_SCREEN:
	  HandleMainSceneInput (deltaTime);
	break;
  default:
	break;
  }
}

void InputHandler::HandleMainSceneInput (float deltaTime)
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

void InputHandler::HandleMenuSceneInput (float deltaTime)
{
  if (App::IsKeyPressed (VK_SPACE)) {
	m_Scene->SetScreen (MAIN_SCREEN);
	m_Scene->Init();
  }
}
