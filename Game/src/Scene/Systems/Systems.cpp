#include "stdafx.h"
#include "Systems.h"
#include "../../Graphics3D/Camera/Camera.h"
#include "../Scene.h"
#include "../GameObjecs/Enemy/Enemy.h"
#include "../GameObjecs/Player/Player.h"


void Systems::SetMainScene(Scene &scene)
{
  Camera::mainCamera.transform = Transform();

  Camera::mainCamera.transform.position = Vector3 (-6.18, 7.38, -6.72);
  Camera::mainCamera.transform.rotation = Vector3 (0, -0.42, 0); 
  
  //int newEntityId = scene.InstantiateNewEntity();
  //scene.components.GetMeshFromID (newEntityId).LoadTrianglesFromObjectFile (".\\TestData\\mountains.obj");

  Player().Init (scene);
}
void Systems::SetMenuScene (Scene &scene)
{
}

void Systems::MovePlayer (Scene &scene, const Vector3 &movement)
{
  Transform &playerTransform = scene.components.GetTransformFromID (scene.GetPlayer().GetSceneId());

  playerTransform.position += (movement * Player::speed);
}

void Systems::ShootBullet (Scene &scene)
{
  Bullet &newBullet = Bullet::InstantiateInScene (scene);


  scene.components.GetTransformFromID (newBullet.GetSceneId()).position =
    scene.components.GetTransformFromID (scene.GetPlayer().GetSceneId()).position + Vector3 (0, 0, 10);
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
	}
  }
}

void Systems::UpdateEnemies (Scene &scene)
{
 /* for (const auto &id : scene.enemyObjs) {
	scene.components.GetAIFromID (id).Update(id, scene);
  }*/
}

int Systems::RandInt (int min, int max)
{
  return rand() % (max - min + 1) + min;
}
float Systems::RandFloat()
{
  return (float)rand() / (float)RAND_MAX;
}
