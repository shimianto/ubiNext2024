#include "stdafx.h"
#include "Bullet.h"
#include "../../Scene.h"

Bullet &Bullet::InstantiateInScene (Scene &scene, Vector3 position, Vector3 direction)
{
  int poolId = scene.GetBullets().InstantiateNextAvailable();

  assert (poolId >= 0);

  Bullet &b = scene.GetBullets().GetElementByID (poolId);
  b.poolId_ = poolId;

  if (b.scenId_ == -1) {
	b.scenId_ = scene.InstantiateNewEntity();
	Mesh &mesh = scene.components.GetMeshFromID (b.scenId_);
	mesh.LoadTrianglesFromObjectFile ("./data/sphere3d.obj");
	mesh.col = Color (1, 0, 1, 1);

	scene.components.GetTransformFromID (b.scenId_).scale = Vector3 (0.04f, 0.04f, 0.04f);
	scene.components.GetColliderFromID (b.scenId_).radius = 1;

  } else {
	scene.EnableEntity (b.scenId_);
	b.lifetime = b.maxLifetime_;
  }

  Physics &physics = scene.components.GetPhysicsFromID (b.scenId_);
  physics.velocity = direction.Normalize() * b.speed;
  scene.components.GetTransformFromID (b.scenId_).position = position;

  return b;
}

Bullet::Bullet (int speed, int lifetime) : 
	GameObject(), 
	maxLifetime_ (lifetime), speed(speed),
	lifetime (lifetime)
{

}
