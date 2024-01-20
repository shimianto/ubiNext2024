#include "stdafx.h"
#include "Systems.h"
#include "../../Graphics3D/Camera/Camera.h"
#include "../Scene.h"
#include "../Managers/UIManager/UIManager.h"
#include "../GameObjecs/Enemy/Enemy.h"
#include "../GameObjecs/Player/Player.h"
#include "../../Math/Vector3/Vector3.h"
#include "../../Math/Utils/Utils.h"


void Systems::SetMainScene(Scene &scene)
{
  Camera::mainCamera.transform = Transform();

  //Camera::mainCamera.transform.position = Vector3 (-6.18, 7.38, -6.72);
  //Camera::mainCamera.transform.rotation = Vector3 (0, -0.42, 0); 
  
  //int newEntityId = scene.InstantiateNewEntity();
  //scene.components.GetMeshFromID (newEntityId).LoadTrianglesFromObjectFile (".\\TestData\\mountains.obj");

  Player::InstantiateInScene (scene);
  scene.waveController.Init(scene, 2, 0, 5, 2, 1);
  scene.waveController.StartNextWave (scene);
}
void Systems::SetMenuScene (Scene &scene)
{
}

void Systems::ChargePlayer (Scene &scene)
{
  Player &p = scene.GetPlayer();
  Physics &playerPhysics = scene.components.GetPhysicsFromID (p.GetSceneId());

  if (playerPhysics.velocity == Vector3() && p.moveForce < p.maxPower) {
	p.moveForce += p.chargeRate;
  }
}

void Systems::ShootPlayer (Scene &scene, const float &deltaTime)
{
  Player &p = scene.GetPlayer();
  Physics &playerPhysics = scene.components.GetPhysicsFromID (p.GetSceneId());

  if (p.moveForce > 0 && playerPhysics.velocity == Vector3()) {
	Transform &playerTransform = scene.components.GetTransformFromID (p.GetSceneId());
	Matrix matRot = Matrix::MakeRotationMatrix (playerTransform.rotation);

	// Calculate new forward direction
	Vector3 vForward = ((Vector3 (0, 1, 0)) * matRot).Normalize();
	vForward.z = 0;

	playerPhysics.velocity = vForward * p.moveForce;
	p.moveForce = 0;
  }

}

void Systems::RotatePlayer (Scene &scene, const Vector3 &rotation)
{
  Transform &playerTransform = scene.components.GetTransformFromID (scene.GetPlayer().GetSceneId());
  //Physics &playerPhysics = scene.components.GetPhysicsFromID (scene.GetPlayer().GetSceneId());

  //if(playerPhysics.velocity == Vector3())
	playerTransform.rotation.z += rotation.x;
}

void Systems::CheckCollisions (Scene &scene)
{
  Player &player = scene.GetPlayer();
  Pool<Enemy> enemyPool = scene.GetEnemies(); 

  for (auto &poolId : enemyPool.GetInUseElements()) {
	Enemy &e = enemyPool.GetElementByID (poolId);

	if (Collider::CheckCollision (scene, player.GetSceneId(), e.GetSceneId())) {
	  scene.DisableEntity (e.GetSceneId());
	  scene.GetEnemies().DisableElement (poolId);
	} 
  }

  if (scene.waveController.IsWaveDone(scene)) {
	scene.waveController.StartNextWave (scene);
  }
}

void Systems::UpdatePlayer (Scene &scene, const float &deltaTime)
{
  Player &p = scene.GetPlayer();
  Transform &playerTransform = scene.components.GetTransformFromID (p.GetSceneId());
  Physics &playerPhysics = scene.components.GetPhysicsFromID (p.GetSceneId());

  UIBar &chargeBar = scene.uiManager_->GetActiveUI (scene).GetBarFromId (p.chargeBarId);
  chargeBar.fill = (p.moveForce / p.maxPower);
  chargeBar.fill = chargeBar.fill > 1 ? 1 : chargeBar.fill;
  chargeBar.color = Color (chargeBar.fill, 1 - chargeBar.fill, 0);

  scene.uiManager_->GetActiveUI (scene).UpdateBarFromId (p.chargeBarId, chargeBar);

  ExecuteEntityPhysics (playerTransform, playerPhysics, deltaTime);
}

void Systems::ExecuteEntityPhysics (Transform &entityTransform, Physics &entityPhysics, const float &deltaTime)
{

  //Update pos
  entityTransform.position += entityPhysics.velocity / deltaTime;

  //Bounce on boundaries
  if (entityTransform.position.x < Physics::ENVIRONMENT_LOWER_BOUDS.x) {
	entityPhysics.velocity.x *= -1;
	entityTransform.position.x = Physics::ENVIRONMENT_LOWER_BOUDS.x;
  } 
  else if(entityTransform.position.x > Physics::ENVIRONMENT_UPPER_BOUDS.x) {
	entityPhysics.velocity.x *= -1;
	entityTransform.position.x = Physics::ENVIRONMENT_UPPER_BOUDS.x;
  }
  if (entityTransform.position.y < Physics::ENVIRONMENT_LOWER_BOUDS.y) {
	entityPhysics.velocity.y *= -1;
	entityTransform.position.y = Physics::ENVIRONMENT_LOWER_BOUDS.y;
  }
  else if (entityTransform.position.y > Physics::ENVIRONMENT_UPPER_BOUDS.y) {
	entityPhysics.velocity.y *= -1;
	entityTransform.position.y = Physics::ENVIRONMENT_UPPER_BOUDS.y;
  }

	//Gravity
  if (entityPhysics.gravity) {
	  if (entityTransform.position.y > Physics::ENVIRONMENT_LOWER_BOUDS.y+1) {
		entityPhysics.velocity.y -= entityPhysics.gravityForce;
	  } else {
	    entityPhysics.velocity.x *= 0.6;
	    entityPhysics.velocity.y *= 0.6;
	  }
  }

  //Execute drag
  if (entityPhysics.velocity.x != 0) {
	if (entityPhysics.velocity.x < 0) {
	  entityPhysics.velocity.x += entityPhysics.drag;
	} else {
	  entityPhysics.velocity.x -= entityPhysics.drag;
	}
  }
  if (entityPhysics.velocity.y != 0) {
	if (entityPhysics.velocity.y < 0) {
	  entityPhysics.velocity.y += entityPhysics.drag;
	} else {
	  entityPhysics.velocity.y -= entityPhysics.drag;
	}
  }
  

  //Set vel to zero if within variance
  if (entityPhysics.velocity.x <= entityPhysics.drag && entityPhysics.velocity.x >= -entityPhysics.drag) {
	entityPhysics.velocity.x = 0;
  }
  if (entityPhysics.velocity.y <= entityPhysics.drag && entityPhysics.velocity.y >= -entityPhysics.drag) {
	entityPhysics.velocity.y = 0;
  }
}

void Systems::UpdateEnemies (Scene &scene, const float &deltaTime)
{
  Pool<Enemy> &enemyPool = scene.GetEnemies();
  for (const auto &poolId : enemyPool.GetInUseElements()) {
	Enemy &enemy = enemyPool.GetElementByID (poolId);
	Transform &enemyTransform = scene.components.GetTransformFromID (enemy.GetSceneId());
	Physics &enemyPhysics = scene.components.GetPhysicsFromID (enemy.GetSceneId());
	BaseAI &enemyAI = scene.components.GetAIFromID (enemy.GetSceneId());

	ExecuteEntityPhysics (enemyTransform, enemyPhysics, deltaTime);

	//Run AI
	switch (enemyAI.GetState()) {
	case PATROLLING:
	  if (enemyPhysics.velocity == Vector3()) {
		enemyPhysics.velocity = Vector3(Utils::RandInt(-1,1)) * enemy.moveForce;
	  }
	  break;
	default:
	  break;
	}
  }
}

void Systems::UpdateEnemyShooters (Scene &scene, const float &deltaTime)
{
  Player &player = scene.GetPlayer();
  Transform &playerTransf = scene.components.GetTransformFromID (player.GetSceneId());

  Pool<EnemyShooter> &enemyShootersPool = scene.GetEnemyShooters();
  
  for (auto &poolId	: enemyShootersPool.GetInUseElements()) {
	EnemyShooter &enemy = enemyShootersPool.GetElementByID (poolId);
	Transform &enemyTransform = scene.components.GetTransformFromID (enemy.GetSceneId());
	BaseAI &enemyAI = scene.components.GetAIFromID (enemy.GetSceneId());
	
	enemy.coolDownTimer -= 1;

	//Run AI
	switch (enemyAI.GetState()) {
	case SHOOTING:
	  if (enemy.coolDownTimer <= 0) {
		ShootBullet (scene, enemyTransform, playerTransf);
		enemy.ResetCooldown();
	  }
	  break;
	default:
	  break;
	}
  }
}

void Systems::ShootBullet (Scene &scene, Transform &enemyTransform, Transform &playerTransf)
{
  Vector3 spawn = enemyTransform.position;
  Vector3 direction = (playerTransf.position - enemyTransform.position);
  direction.z = 0;

  Bullet::InstantiateInScene (scene, spawn, direction);
}

void Systems::UpdateBullets (Scene &scene, const float &deltaTime)
{
  Pool<Bullet> &bulletPool = scene.GetBullets();
  std::set<int> activeBullets = bulletPool.GetInUseElements();

  for (auto &bulletId : activeBullets) {
	Bullet &b = bulletPool.GetElementByID (bulletId);

	b.lifetime--;

	if (b.lifetime <= 0) {
	  bulletPool.DisableElement (bulletId);
	  scene.DisableEntity (b.GetSceneId());
	  continue;
	}
	Transform &transf = scene.components.GetTransformFromID (b.GetSceneId());
	Physics &phys = scene.components.GetPhysicsFromID (b.GetSceneId());

	ExecuteEntityPhysics (transf, phys, deltaTime);
  }
}
