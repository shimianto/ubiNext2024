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
  
  Systems::UpdatePlayer (*this, deltaTime);
  Systems::UpdateEnemies (*this, deltaTime);
  Systems::UpdateEnemyShooters(*this, deltaTime);
  Systems::UpdateBullets (*this, deltaTime);
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

void Scene::EnableEntity (const int &id)
{
  entityManager_.Enable (id);
}

void Scene::DisableEntity (const int &id)
{
  entityManager_.Disable (id);
}

void Scene::SetPlayer (Player &player)
{
  player_ = player;
}

Player &Scene::GetPlayer()
{
  return player_;
}

Pool<Bullet> &Scene::GetBullets()
{
  return bullets_;
}

Pool<Enemy> &Scene::GetEnemies()
{
  return enemies_;
}

Pool<EnemyShooter> &Scene::GetEnemyShooters()
{
  return enemyShooters_;
}

void Scene::SetScene (const SceneType &type)
{
  entityManager_.ClearEntities();
  components.ClearComponents();
  ClearGameObjects();
  player_ = Player();

  activeScene_ = type;
  switch (type) {
  case MENU_SCENE:
	Systems::SetUpMenuScene(*this);
	break;
  case MAIN_SCENE:
	Systems::SetUpMainScene(*this);
	break;
  case GRID_TEST:
  {
	  int newGrid = InstantiateNewEntity();
	  components.GetGridFromID (newGrid).Init (6, 6, Vector3 (100, 100), Vector3 (160, 80));
  }
	  break;
  case PARTICLES_SCENE:
	  Systems::SetUpParticleScene (*this);
	  break;
  default:
	break;
  }
}

void Scene::ClearGameObjects()
{
  bullets_.Clear();
  enemies_.Clear();
  enemyShooters_.Clear();

  waveController = WaveController();
}
