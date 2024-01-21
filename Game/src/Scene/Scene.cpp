#include "Scene.h"
#include "stdafx.h"
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


 
  UpdatePlayer (deltaTime);
  UpdateEnemies (deltaTime);

   for (auto &poolId : enemyShooters_.GetInUseElements()) {
	EnemyShooter &enemy = enemyShooters_.GetElementByID (poolId);
	enemy.coolDownTimer -= 1;
	Systems::ExecuteEnemyShooterAI(*this, enemy);
  }
  
  Systems::UpdateBullets (*this, deltaTime);

  //Try new wave
  if (waveController.IsWaveDone (*this)) {
	waveController.StartNextWave (*this);
  }

  bool changeScene = false;
  for (auto &btnId : buttons_.GetInUseElements()) {
	Button &btn = buttons_.GetElementByID (btnId);
	if (Collider::CheckCollision (*this, btn.GetSceneId(), player_.GetSceneId())) {
	  changeScene = true;
	}
  }
  if (changeScene) {
	  SetScene (MAIN_SCENE);
  }
}

void Scene::UpdateEnemies (float &deltaTime)
{
  //Enemies
  std::set<int> enemiesIdsCopy = enemies_.GetInUseElements();
  for (const auto &poolId : enemiesIdsCopy) {
	  Enemy &enemy = enemies_.GetElementByID (poolId);
	  Transform &enemyTransform = components.GetTransformFromID (enemy.GetSceneId());
	  Physics &enemyPhysics = components.GetPhysicsFromID (enemy.GetSceneId());

	  Systems::ExecuteEntityPhysics (enemyTransform, enemyPhysics, deltaTime);
	  Systems::ExecuteEnemyAI (*this, &enemy);

	  //Check Collisions
	  if (player_.GetSceneId() != -1 && Collider::CheckCollision (*this, player_.GetSceneId(), enemy.GetSceneId())) {
	  Systems::DisableGameObjectInScene (*this, &enemy, &enemies_);
	  }
  }
}

void Scene::UpdatePlayer (float &deltaTime)
{
  // Player
  if (player_.GetSceneId() >= 0) {
	  Transform &playerTransform = components.GetTransformFromID (player_.GetSceneId());
	  Physics &playerPhysics = components.GetPhysicsFromID (player_.GetSceneId());
	  Health &pHealth = components.GetHealthFromID (player_.GetSceneId());

	  // Update Charge bar
	  uiManager_->GetActiveUI (*this).UpdateBarFromId (player_.chargeBarId, player_.GetChargeBar());

	  Systems::ExecuteEntityPhysics (playerTransform, playerPhysics, deltaTime);
	  Systems::TryDamageToPlayer (player_, pHealth);

	  if (pHealth.GetValue() <= 0) {
	  SetScene (MENU_SCENE);
	  }

	  UIBar &healthBar = uiManager_->GetActiveUI (*this).GetBarFromId (player_.healthBarId);
	  healthBar.fill = (float)pHealth.GetValue() / (float)pHealth.GetMax();

	  uiManager_->GetActiveUI (*this).UpdateBarFromId (player_.healthBarId, healthBar);
  }
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

Pool<Button> &Scene::GetButtons()
{
  return buttons_;
}

void Scene::SetScene (const SceneType &type)
{
  entityManager_.ClearEntities();
  components.ClearComponents();
  uiManager_->GetActiveUI (*this).Clear();
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
  default:
	break;
  }
}

void Scene::ClearGameObjects()
{
  bullets_.Clear();
  enemies_.Clear();
  enemyShooters_.Clear();
  buttons_.Clear();

  waveController = WaveController();
}
