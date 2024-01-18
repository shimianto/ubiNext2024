#include "Scene.h"
#include <list>
#include "stdafx.h"
#include "Components/Mesh/Mesh.h"
#include "../Renderer/Renderer.h"
#include "../InputHandler/InputHandler.h"
#include "Managers//UIManager/UIManager.h"

Scene::Scene()
{
}

void Scene::Init (UIManager &uiManager)
{
  uiManager_ = &uiManager;

  uiManager_->Init(*this);

  inputHandler_.Init (*this);
  renderer_.Init (*this);
}


void Scene::Update (float deltaTime)
{
  uiManager_->Update (*this);

  UpdateScreen();
  inputHandler_.HandleInput (deltaTime);
  renderer_.Update (deltaTime);
  //particles_.Update(deltaTime);
}

void Scene::Render()
{
  uiManager_->Render (*this);

  RenderScreen();
  renderer_.Render();
  //particles_.Render();
}

void Scene::Shutdown()
{
}

SceneType Scene::GetOpenedScene()
{
  return activeScene_;
}

void Scene::SetScene (SceneType type)
{
  entityManager_.ClearEntities();
  components.ClearComponents();
  activeScene_ = type;
  switch (type) {
  case MENU_SCENE:
	SetMenuScene();
	break;
  case MAIN_SCENE:
	SetMainScene();
	break;
  case PARTICLES_SCENE:
	InstantiateNewEntity();
  default:
	break;
  }
}

int Scene::InstantiateNewEntity()
{
  int entId = entityManager_.RegisterEntity (BaseEntity());
  components.InstantiateComponents (entId);

  return entId;
}

BaseEntity Scene::GetEntityFromID (int id)
{
  return entityManager_.GetEntityFromID(id);
}

std::set<int> Scene::GetActiveEntities() const
{
  return entityManager_.GetActiveEntities();
}

const SceneType Scene::GetActiveScene() const
{
  return activeScene_;
}

void Scene::SetMainScene()
{
  Camera::mainCamera.transform = Transform();

  int newEntityId = InstantiateNewEntity();
  components.GetMeshFromID(newEntityId).LoadTrianglesFromObjectFile (".\\TestData\\mountains.obj");
}

void Scene::SetMenuScene()
{
  int newEntityId = InstantiateNewEntity();
  components.GetMeshFromID (newEntityId).LoadTrianglesFromObjectFile (".\\TestData\\teapot.obj");
}

void Scene::UpdateScreen()
{
  switch (activeScene_) {
  case MENU_SCENE:
	break;
  case MAIN_SCENE:
	break;
  default:
	break;
  }
}

void Scene::RenderScreen()
{
  switch (activeScene_) {
  case MENU_SCENE:
	break;
  case MAIN_SCENE:
	break;
  default:
	break;
  }
}


