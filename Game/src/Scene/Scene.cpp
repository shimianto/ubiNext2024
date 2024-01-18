#include "Scene.h"
#include <list>
#include "stdafx.h"
#include "Components/Mesh/Mesh.h"
#include "../Renderer/Renderer.h"
#include "../InputHandler/InputHandler.h"
#include "Managers//UIManager/UIManager.h"
#include "Systems/Systems.h"

Scene::Scene()
{
}

void Scene::Init (UIManager &uiManager, const SceneType &sceneType)
{
  uiManager_ = &uiManager;

  inputHandler_.Init (*this);
  uiManager_->Init(*this);
  renderer_.Init (*this);

  SetScene (sceneType);
}


void Scene::Update (float deltaTime)
{
  inputHandler_.HandleInput (deltaTime);

  uiManager_->Update (*this);
  renderer_.Update (deltaTime);
  
}

void Scene::Render()
{
  uiManager_->Render (*this);
  renderer_.Render();
}

void Scene::Shutdown()
{
  entityManager_.ClearEntities();
  components.ClearComponents();
}


const int Scene::InstantiateNewEntity()
{
  int entId = entityManager_.InstantiateNewEntity ();
  components.InstantiateComponents (entId);

  return entId;
}

const SceneType Scene::GetActiveScene() const
{
  return activeScene_;
}

BaseEntity Scene::GetEntityFromID (int id)
{
  return entityManager_.GetEntityFromID(id);
}

std::set<int> Scene::GetActiveEntities() const
{
  return entityManager_.GetActiveEntities();
}

void Scene::SetScene (const SceneType &type)
{
  entityManager_.ClearEntities();
  components.ClearComponents();

  activeScene_ = type;
  switch (type) {
  case MENU_SCENE:
	Systems::SetMenuScene(*this);
	break;
  case MAIN_SCENE:
	Systems::SetMainScene(*this);
	break;
  case GRID_TEST:
  {
	  int newGrid = InstantiateNewEntity();
	  components.GetGridFromID (newGrid).Init (6, 6, Vector3 (100, 100), Vector3 (160, 80));
  }
	  break;
  case PARTICLES_SCENE:
	  InstantiateNewEntity();
	  break;
  default:
	break;
  }
}
