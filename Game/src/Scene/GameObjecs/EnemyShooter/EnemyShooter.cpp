#include "stdafx.h"
#include "EnemyShooter.h"
#include "../../Scene.h"
#include "../../../Math/Vector3/Vector3.h"

EnemyShooter &EnemyShooter::InstantiateInScene (Scene &scene, Vector3 position, Vector3 rotation)
{
  int poolId = scene.GetEnemyShooters().InstantiateNextAvailable();

  assert (poolId >= 0);

  EnemyShooter &newEnemy = scene.GetEnemyShooters().GetElementByID (poolId);
  newEnemy.poolId_ = poolId;

  if (newEnemy.scenId_ == -1) {
	newEnemy.scenId_ = scene.InstantiateNewEntity();
	Mesh &mesh = scene.components.GetMeshFromID (newEnemy.scenId_);
	mesh.LoadTrianglesFromObjectFile ("./data/cylinder3d.obj");
	mesh.col = Color (1, 0, 0, 0);

	scene.components.GetTransformFromID (newEnemy.scenId_).scale = Vector3 (0.06f, 0.06f, 0.06f);

	scene.components.GetColliderFromID (newEnemy.scenId_).radius = 2;
	scene.components.GetAIFromID (newEnemy.scenId_).SetState (SHOOTING);
	scene.components.GetPhysicsFromID (newEnemy.scenId_).drag = 0.1f;

  } else {
	scene.EnableEntity (newEnemy.scenId_);
  }

  scene.components.GetTransformFromID (newEnemy.scenId_).position = position;
  scene.components.GetTransformFromID (newEnemy.scenId_).rotation = rotation;

  return newEnemy;
}

EnemyShooter::EnemyShooter() : GameObject(), shootCooldown_ (100), coolDownTimer (shootCooldown_), projectileForce (10)
{
}

void EnemyShooter::ResetCooldown()
{
  coolDownTimer = shootCooldown_;
}
