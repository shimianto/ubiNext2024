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
  Transform &playerTransform = scene.components.GetTransformFromID (scene.GetPlayer().GetId());

  playerTransform.position += (movement * Player::speed);
}

void Systems::ShootBullet (Scene &scene)
{
  Bullet newBullet;
  newBullet.Init(scene);

  if (newBullet.GetId() == -1) {
	return;
  }

  scene.components.GetTransformFromID (newBullet.GetId()).position =
    scene.components.GetTransformFromID (scene.GetPlayer().GetId()).position + Vector3 (0, 0, 10);
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
