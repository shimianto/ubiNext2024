#include "stdafx.h"
#include "Bullet.h"
#include "../../Scene.h"

Bullet &Bullet::InstantiateInScene (Scene &scene)
{
  int poolId = scene.GetBullets().InstantiateNextAvailable();

  assert (poolId >= 0);

  Bullet &b = scene.GetBullets().GetElementByID (poolId);
  b.poolId_ = poolId;

  if (b.scenId_ == -1) {
	b.scenId_ = scene.InstantiateNewEntity();
	scene.components.GetMeshFromID (b.scenId_).LoadTrianglesFromObjectFile ("./data/sphere3d.obj");
	scene.components.GetTransformFromID (b.scenId_).scale = Vector3 (0.1f, 0.1f, 0.1f);

  } else {
	scene.EnableEntity (b.scenId_);
	b.lifetime = b.maxLifetime_;
  }

  return b;
}

Bullet::Bullet (int lifetime) : 
	GameObject(), 
	maxLifetime_ (lifetime), lifetime (lifetime)
{

}

int Bullet::Init (Scene &scene)
{
  return scenId_;
}
