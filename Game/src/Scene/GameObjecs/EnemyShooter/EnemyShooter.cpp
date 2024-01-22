#include "stdafx.h"
#include "EnemyShooter.h"
#include "../../Scene.h"
#include "../../../Math/Vector3/Vector3.h"

void EnemyShooter::InstantiateInScene (Scene &scene, Vector3 position, Vector3 rotation)
{
  int poolId = scene.GetEnemyShooters().InstantiateNextAvailable();

    if (poolId == -1) {
		return;
	}

  EnemyShooter &newEnemy = scene.GetEnemyShooters().GetElementByID (poolId);
  newEnemy.poolId_ = poolId;

  if (newEnemy.scenId_ == -1) {
	newEnemy.scenId_ = scene.InstantiateNewEntity();
	Mesh &mesh = scene.components.GetMeshFromID (newEnemy.scenId_);
	mesh.LoadTrianglesFromObjectFile ("./data/sphere3d.obj");
	mesh.col = Color (1, 0, 0, 0);

	ParticleSystem &ps = scene.components.GetParticlesFromID (newEnemy.scenId_);
	ps.mesh.LoadTrianglesFromObjectFile ("./data/cube3d.obj");
	ps.SetParticleScale (0.8f);
	ps.SetParticleLife (30);

	scene.components.GetTransformFromID (newEnemy.scenId_).scale = Vector3 (0.065f, 0.065f, 0.065f);
	scene.components.GetColliderFromID (newEnemy.scenId_).radius = 2;
	scene.components.GetPhysicsFromID (newEnemy.scenId_).drag = 0.1f;

	scene.components.GetAIFromID (newEnemy.scenId_).SetState (PATROLLING);

  } else {
	scene.EnableEntity (newEnemy.scenId_);
  }

  scene.components.GetTransformFromID (newEnemy.scenId_).position = position;
  scene.components.GetTransformFromID (newEnemy.scenId_).rotation = rotation;
}

EnemyShooter::EnemyShooter() : Enemy(), shootCooldown_ (80), coolDownTimer (shootCooldown_), projectileForce (30)
{
}

void EnemyShooter::ResetCooldown()
{
  coolDownTimer = shootCooldown_;
}
