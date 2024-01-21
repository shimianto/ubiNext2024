#include "stdafx.h"
#include "EnemyPatrolling.h"
#include "../../../../Scene.h"
#include "../../BaseAI.h"
#include "../../../Transform/Transform.h"
#include "../../../Physics/Physics.h"
#include "../../../Particles/ParticleSystem.h"
#include "../../../Mesh/Mesh.h"
#include "../../../../../Math/Utils/Utils.h"
#include "../../../../Managers/AudioManager/AudioManager.h"

EnemyPatrolling::EnemyPatrolling (const float &dashForce) : dashForce_ (dashForce)
{
  aiState = PATROLLING;
}

void EnemyPatrolling::OnExecute (Scene &scene, const int &entityId)
{
  Transform &enemyTransform = scene.components.GetTransformFromID (entityId);
  Physics &enemyPhysics = scene.components.GetPhysicsFromID (entityId);
  Mesh &entityMesh = scene.components.GetMeshFromID (entityId);
  ParticleSystem &entityParticles = scene.components.GetParticlesFromID (entityId);

  if (enemyPhysics.velocity == Vector3()) {
	enemyPhysics.velocity = Vector3 (Utils::RandInt (-2, 2), Utils::RandInt (-2, 2)) * dashForce_;

	entityParticles.SpawnParticles (
	  5, enemyTransform.position - enemyPhysics.velocity.Normalize() * 2, (enemyPhysics.velocity.Normalize() * -1) / 2, entityMesh.col);

	if (!App::IsSoundPlaying (AudioManager::ENEMY_DASH_SFX)) {
	  App::PlaySound (AudioManager::ENEMY_DASH_SFX);
	}
  }
}
