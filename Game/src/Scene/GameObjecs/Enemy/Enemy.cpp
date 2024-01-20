#include "stdafx.h"
#include "Enemy.h"
#include "../../Scene.h"

Enemy &Enemy::InstantiateInScene (Scene &scene, Vector3 position)
{
  int poolId = scene.GetEnemies().InstantiateNextAvailable();

  assert (poolId >= 0);

  Enemy &newEnemy = scene.GetEnemies().GetElementByID (poolId);
  newEnemy.poolId_ = poolId;

  if (newEnemy.scenId_ == -1) {
	newEnemy.scenId_ = scene.InstantiateNewEntity();
	scene.components.GetMeshFromID (newEnemy.scenId_).LoadTrianglesFromObjectFile ("./data/cube3d.obj");
	scene.components.GetTransformFromID (newEnemy.scenId_).scale = Vector3 (2, 2, 2);
	scene.components.GetColliderFromID (newEnemy.scenId_).radius = 2;

  } else {
	scene.EnableEntity (newEnemy.scenId_);
  }

   scene.components.GetTransformFromID (newEnemy.scenId_).position = position;

  return newEnemy;
}