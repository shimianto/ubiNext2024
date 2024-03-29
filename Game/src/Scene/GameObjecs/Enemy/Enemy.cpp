#include "stdafx.h"
#include "Enemy.h"
#include "../../Scene.h"
#include "../../../Math/Vector3/Vector3.h"


void Enemy::InstantiateInScene (Scene &scene, Vector3 position)
{
  int poolId = scene.GetEnemies().InstantiateNextAvailable();

  if (poolId == -1) {
	return;
  }

  Enemy &newEnemy = scene.GetEnemies().GetElementByID (poolId);
  newEnemy.poolId_ = poolId;

  if (newEnemy.scenId_ == -1) {
	newEnemy.scenId_ = scene.InstantiateNewEntity();
	Mesh &mesh = scene.components.GetMeshFromID (newEnemy.scenId_);
	mesh.LoadTrianglesFromObjectFile ("./data/sphere3d.obj");
	mesh.col = Color (0, 0, 1, 0);

	ParticleSystem &ps = scene.components.GetParticlesFromID (newEnemy.scenId_);
	ps.mesh.LoadTrianglesFromObjectFile ("./data/cube3d.obj");
	ps.SetParticleScale (0.8f);
	ps.SetParticleLife (30);

	scene.components.GetAIFromID (newEnemy.scenId_).SetState (PATROLLING);


	scene.components.GetTransformFromID (newEnemy.scenId_).scale = Vector3 (0.065f, 0.065f, 0.065f);
	scene.components.GetColliderFromID (newEnemy.scenId_).radius = 2;
	scene.components.GetPhysicsFromID (newEnemy.scenId_).drag = 0.1f;

  } else {
	scene.EnableEntity (newEnemy.scenId_);
  }
   scene.components.GetTransformFromID (newEnemy.scenId_).position = position;
}

Enemy::Enemy() : GameObject(), moveForce(7)
{
}
