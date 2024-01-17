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
  switch (m_Scene->GetOpenedScene()) {
  case MENU_SCENE:
	  HandleMenuSceneInput (deltaTime);
	break;
  case MAIN_SCENE:
	  HandleMainSceneInput (deltaTime);
	break;
  case PARTICLES_SCENE:
	HandleParticleSceneInput();
	break;
  default:
	break;
  }
}

void InputHandler::HandleParticleSceneInput()
{
  if (App::IsKeyPressed (VK_LBUTTON)) {
	Vector3 position;
	App::GetMousePos (position.x, position.y);
	m_Scene->PlayParticlesAtPosition (position);
  }
}

void InputHandler::HandleMainSceneInput (float deltaTime)
{
  if (App::GetController().GetLeftThumbStickY() > 0.5f) {
	Camera::mainCamera.transform.position.z += 1 / deltaTime;
  } else if (App::GetController().GetLeftThumbStickY() < -0.5f) {
	Camera::mainCamera.transform.position.z -= 1 / deltaTime;
  }
  if (App::GetController().GetLeftThumbStickX() > 0.5f) {
	Camera::mainCamera.transform.rotation.y += 1 / deltaTime;
  } else if (App::GetController().GetLeftThumbStickX() < -0.5f) {
	Camera::mainCamera.transform.rotation.y -= 1 / deltaTime;
  }
  if (App::GetController().CheckButton (XINPUT_GAMEPAD_DPAD_UP, false)) {
	Camera::mainCamera.transform.position.y += 1 / deltaTime;
  }
  if (App::GetController().CheckButton (XINPUT_GAMEPAD_DPAD_DOWN, false)) {
	Camera::mainCamera.transform.position.y -= 1 / deltaTime;
  }
  if (App::GetController().CheckButton (XINPUT_GAMEPAD_DPAD_LEFT, false)) {
	Camera::mainCamera.transform.position.x += 1 / deltaTime;
  }
  if (App::GetController().CheckButton (XINPUT_GAMEPAD_DPAD_RIGHT, false)) {
	Camera::mainCamera.transform.position.x -= 1 / deltaTime;
  }
}

void InputHandler::HandleMenuSceneInput (float deltaTime)
{
  if (App::IsKeyPressed (VK_SPACE)) {
	m_Scene->SetScene (MAIN_SCENE);
	//m_Scene->Init();
  }
}
