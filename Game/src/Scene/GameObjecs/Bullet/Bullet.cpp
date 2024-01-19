#include "stdafx.h"
#include "Bullet.h"
#include "../../Scene.h"

int Bullet::Init (Scene &scene)
{
  int poolId = scene.GetBullets().InstantiateNextAvailable();

  if (poolId == -1) {
	return -1;
  }

  *this = scene.GetBullets().GetElementByID (poolId);
  poolId_ = poolId;

  if (scenId_ == -1) {
	scenId_ = scene.InstantiateNewEntity();
	scene.components.GetMeshFromID (scenId_).LoadTrianglesFromObjectFile ("./data/sphere3d.obj");
	scene.components.GetTransformFromID (scenId_).scale = Vector3 (0.1f, 0.1f, 0.1f);
  }

  return scenId_;
}
