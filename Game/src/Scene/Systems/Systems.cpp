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
  
  Enemy::InstantiateInScene (scene, Vector3 (20, 0, 0));
}
void Systems::SetMenuScene (Scene &scene)
{
}

void Systems::ChargePlayer (Scene &scene)
{
  Player &p = scene.GetPlayer();
  Physics &playerPhysics = scene.components.GetPhysicsFromID (p.GetSceneId());

  if (playerPhysics.velocity == Vector3() && p.shootForce < p.maxPower) {
	p.shootForce += p.chargeRate;
  }
}

void Systems::ShootPlayer (Scene &scene, const float &deltaTime)
{
  Player &p = scene.GetPlayer();
  Physics &playerPhysics = scene.components.GetPhysicsFromID (p.GetSceneId());

  if (p.shootForce > 0 && playerPhysics.velocity == Vector3()) {
	Transform &playerTransform = scene.components.GetTransformFromID (p.GetSceneId());
	Matrix matRot = Matrix::MakeRotationMatrix (playerTransform.rotation);

	// Calculate new forward direction
	Vector3 vForward = ((Vector3 (0, 1, 0)) * matRot).Normalize();

	playerPhysics.velocity = vForward * p.shootForce;
	p.shootForce = 0;
  }

}

void Systems::RotatePlayer (Scene &scene, const Vector3 &rotation)
{
  Transform &playerTransform = scene.components.GetTransformFromID (scene.GetPlayer().GetSceneId());
  playerTransform.rotation.z += rotation.x;
}

void Systems::ShootBullet (Scene &scene)
{
  Player &player = scene.GetPlayer();

  /*if (player.fireCoolDown > 0) {
	return;
  }

  player.StartFireCooldown();

  Bullet &newBullet = Bullet::InstantiateInScene (scene);

  scene.components.GetTransformFromID (newBullet.GetSceneId()).position =
    scene.components.GetTransformFromID (player.GetSceneId()).position + Vector3 (0, 0, 10);*/
}

void Systems::CheckCollisions (Scene &scene)
{
  Player &player = scene.GetPlayer();
  Pool<Enemy> &enemyPool = scene.GetEnemies();

  for (auto &enemyId : enemyPool.GetInUseElements()) {
	Enemy &e = enemyPool.GetElementByID (enemyId);

	if (Collider::CheckCollision (scene, player.GetSceneId(), e.GetSceneId())) {
	  scene.components.GetMeshFromID (e.GetSceneId()).col = Color (1, 0, 0, 0);
	} else {
	  scene.components.GetMeshFromID (e.GetSceneId()).col = Color (0, 0, 1, 0);
	}
  }
}

void Systems::UpdatePlayer (Scene &scene, const float &deltaTime)
{
  Player &p = scene.GetPlayer();
  Transform &playerTransform = scene.components.GetTransformFromID (p.GetSceneId());
  Physics &playerPhysics = scene.components.GetPhysicsFromID (p.GetSceneId());

  UIBar &chargeBar = scene.uiManager_->GetActiveUI (scene).GetBarFromId (p.chargeBarId);
  chargeBar.fill = (p.shootForce / p.maxPower);
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
  if (entityTransform.position.x < Physics::ENVIRONMENT_LOWER_BOUDS.x || entityTransform.position.x > Physics::ENVIRONMENT_UPPER_BOUDS.x) {
	entityPhysics.velocity.x *= -1;
  }
  if (entityTransform.position.y < Physics::ENVIRONMENT_LOWER_BOUDS.y || entityTransform.position.y > Physics::ENVIRONMENT_UPPER_BOUDS.y) {
	entityPhysics.velocity.y *= -1;
  }


	//Gravity
  if (entityPhysics.gravity) {
	  if (entityTransform.position.y > Physics::ENVIRONMENT_LOWER_BOUDS.y) {
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
  if (entityPhysics.velocity.y <= entityPhysics.drag && entityPhysics.velocity.y >= -entityPhysics.drag && entityTransform.position.y < -24) {
	entityPhysics.velocity.y = 0;
  }
}

void Systems::UpdateBullets (Scene &scene)
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

	scene.components.GetTransformFromID (b.GetSceneId()).position += Vector3 (0, 0, b.speed);
  }
}

void Systems::UpdateEnemies (Scene &scene, const float &deltaTime)
{
  Pool<Enemy> enemyPool = scene.GetEnemies();
  for (const auto &poolId : enemyPool.GetInUseElements()) {
	Enemy &enemy = enemyPool.GetElementByID (poolId);
	Transform &enemytransform = scene.components.GetTransformFromID (enemy.GetSceneId());
	Physics &enemyPhysics = scene.components.GetPhysicsFromID (enemy.GetSceneId());
	BaseAI &enemyAI = scene.components.GetAIFromID (enemy.GetSceneId());

	ExecuteEntityPhysics (enemytransform, enemyPhysics, deltaTime);

	//Run AI
	switch (enemyAI.GetState()) {
	case PATROLLING:
	  if (enemyPhysics.velocity == Vector3()) {
		enemyPhysics.velocity = Vector3(Utils::RandInt(-1,1)) * enemy.shootForce;
	  }
	  break;
	default:
	  break;
	}
  }
}
