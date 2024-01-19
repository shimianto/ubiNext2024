#include "stdafx.h"
#include "InputHandler.h"
#include <App/app.h>
#include "../Graphics3D/Camera/Camera.h"
#include "../Scene/Scene.h"
#include "../Scene/Systems/Systems.h"

void InputHandler::Init (Scene &scene)
{
  scene_ = &scene;
}

void InputHandler::HandleInput (float deltaTime)
{
  switch (scene_->GetActiveScene()) {
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
  if (App::IsKeyPressed (VK_RBUTTON)) {
	Particle::DEFAULT_PARTICLE_COL = Color (Systems::RandFloat(), Systems::RandFloat(), Systems::RandFloat());
  }

  if (App::IsKeyPressed (VK_LBUTTON)) {
	Vector3 position;
	App::GetMousePos (position.x, position.y);

	scene_->components.GetParticlesFromID (0).NewParticle (position);
  }
}

void InputHandler::HandleMainSceneInput (float deltaTime)
{
	//Move Camera
  if (App::IsKeyPressed (VK_SHIFT)) {
	  if (App::GetController().GetLeftThumbStickY() > 0.5f) {
		Camera::mainCamera.transform.position.z += 1 / deltaTime;
	  } else if (App::GetController().GetLeftThumbStickY() < -0.5f) {
		Camera::mainCamera.transform.position.z -= 1 / deltaTime;
	  }

	  if (App::GetController().GetLeftThumbStickX() > 0.5f) {
		Camera::mainCamera.transform.rotation.y += 0.5 / deltaTime;
	  } else if (App::GetController().GetLeftThumbStickX() < -0.5f) {
		Camera::mainCamera.transform.rotation.y -= 0.5 / deltaTime;
	  }
	  if (App::IsKeyPressed ('Q')) {
	    Camera::mainCamera.transform.rotation.x -= 0.5 / deltaTime;
	  } else if (App::IsKeyPressed ('E')) {
	    Camera::mainCamera.transform.rotation.x += 0.5 / deltaTime;
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
  else {
	  if (App::GetController().GetLeftThumbStickY() > 0.5f) {
	    Systems::MovePlayer (*scene_, Vector3 (0, 0, 1 / deltaTime));

	  } else if (App::GetController().GetLeftThumbStickY() < -0.5f) {
	    Systems::MovePlayer (*scene_, Vector3 (0, 0, -1 / deltaTime));
	  }
	  if (App::GetController().GetLeftThumbStickX() > 0.5f) {
	    Systems::MovePlayer (*scene_, Vector3 (-1 / deltaTime, 0));
	  } else if (App::GetController().GetLeftThumbStickX() < -0.5f) {
	    Systems::MovePlayer (*scene_, Vector3 (1 / deltaTime, 0));
	  }

	  if (App::IsKeyPressed (VK_SPACE)) {
	    Systems::ShootBullet (*scene_);
	  }
	
  }
}

void InputHandler::HandleMenuSceneInput (float deltaTime)
{
  if (App::IsKeyPressed (VK_SPACE)) {
	scene_->SetScene (MAIN_SCENE);
  }
}
