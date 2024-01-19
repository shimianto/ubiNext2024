#include "stdafx.h"
#include "Enemy.h"
#include "../../Scene.h"

int Enemy::Init (Scene &scene)
{
  int poolId = scene.GetEnemies().InstantiateNextAvailable();

  if (poolId == -1) {
	return -1;
  }

  *this = scene.GetEnemies().GetElementByID (poolId);
  poolId_ = poolId;

  if (scenId_ == -1) {
	  scenId_ = scene.InstantiateNewEntity();
	  scene.components.GetMeshFromID (scenId_).LoadTrianglesFromObjectFile ("./data/cone3d.obj");
	  scene.components.GetTransformFromID (scenId_).scale = Vector3 (0.1f, 0.1f, 0.1f);
	  scene.components.GetAIFromID (scenId_).SetState (PATROLLING);
  }


  //scene.enemyObjs.insert (scenId_);

  return scenId_;
}