#include "stdafx.h"
#include "Systems.h"
#include "../../Graphics3D/Camera/Camera.h"
#include "../Scene.h"
#include "../Managers/UIManager/UIManager.h"
#include "../GameObjecs/Enemy/Enemy.h"
#include "../GameObjecs/Player/Player.h"
#include "../../Math/Vector3/Vector3.h"


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
  if (p.velocity == Vector3() && p.shootPower < p.maxPower) {
	p.shootPower += p.chargeRate;
  }
}

void Systems::ShootPlayer (Scene &scene, const float &deltaTime)
{
  Player &p = scene.GetPlayer();
  if (p.shootPower > 0 && p.velocity == Vector3()) {
	  Transform &playerTransform = scene.components.GetTransformFromID (p.GetSceneId());
	  Matrix matRot = Matrix::MakeRotationMatrix (playerTransform.rotation);

	  // Calculate new forward direction
	  Vector3 vForward = ((Vector3(0,1,0)) * matRot).Normalize();

	  p.velocity = vForward * p.shootPower;
	  p.shootPower = 0;
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

  if (player.fireCoolDown > 0) {
	return;
  }

  player.StartFireCooldown();

  Bullet &newBullet = Bullet::InstantiateInScene (scene);

  scene.components.GetTransformFromID (newBullet.GetSceneId()).position =
    scene.components.GetTransformFromID (player.GetSceneId()).position + Vector3 (0, 0, 10);
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

  UIBar &chargeBar = scene.uiManager_->GetActiveUI (scene).GetBarFromId (p.chargeBarId);
  chargeBar.fill = (p.shootPower / p.maxPower);
  chargeBar.fill = chargeBar.fill > 1 ? 1 : chargeBar.fill;
  chargeBar.color = Color (chargeBar.fill, 1 - chargeBar.fill, 0);

  scene.uiManager_->GetActiveUI (scene).UpdateBarFromId (p.chargeBarId, chargeBar);


  //Gravity
  if (playerTransform.position.y > -24) {
	p.velocity.y -= p.drag;
  }

  if (p.velocity == Vector3 (0, 0, 0)) {
	return;
  }

  //Update pos
  playerTransform.position += p.velocity / deltaTime;

  //Bounce on boundaries
  if (playerTransform.position.x < -35 || playerTransform.position.x > 35) {
	p.velocity.x *= -0.9;
  }
  if (playerTransform.position.y < -25) {
	p.velocity.x *= 0.6;
	p.velocity.y *= -0.6;
  } else if (playerTransform.position.y > 25) {
	p.velocity.y *= -1;
  }


  //Update velocity
  if (p.velocity.x != 0) {
	  if (p.velocity.x < 0)
	  {
		//p.velocity.x += p.drag;
	  } else {
		//p.velocity.x -= p.drag;
	  }
  }
  if (p.velocity.y != 0) {
	  if (p.velocity.y < 0) {
		//p.velocity.y += p.drag;
	  } else {
		//p.velocity.y -= p.drag;
	  }
  }

  //Set vel to zero if within variance
  if (p.velocity.x <= p.drag && p.velocity.x >= -p.drag) {
	p.velocity.x = 0;
  } 
  if (p.velocity.y <= p.drag && p.velocity.y >= -p.drag && playerTransform.position.y < -24) {
	p.velocity.y = 0;
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

void Systems::UpdateEnemies (Scene &scene)
{
 /* for (const auto &id : scene.enemyObjs) {
	scene.components.GetAIFromID (id).Update(id, scene);
  }*/
}
