#include "stdafx.h"
#include "EnemyShooterAttack.h"
#include "../../../../Scene.h"
#include "../../../../Systems/Systems.h"
#include "../../../../../Math/Utils/Utils.h"
#include "EnemyPatrolling.h"

EnemyShooterAttackState::EnemyShooterAttackState (EnemyShooter *enemyShooter) : enemyShooter_(enemyShooter)
{
}

void EnemyShooterAttackState::OnExecute (Scene &scene, const int &entityId)
{

  Player &player = scene.GetPlayer();

  if (player.GetSceneId() == -1) {
	return;
  }

  Transform &playerTransf = scene.components.GetTransformFromID (player.GetSceneId());

  Transform &enemyTransform = scene.components.GetTransformFromID (entityId);
  BaseAI &enemyAI = scene.components.GetAIFromID (entityId);
  Physics &enemyPhysics = scene.components.GetPhysicsFromID (entityId);


  enemyShooter_-> coolDownTimer -= 1;

  if (enemyShooter_->coolDownTimer <= 0) {
	Systems::ShootBullet (scene, enemyTransform, playerTransf);
	enemyShooter_->ResetCooldown();
	
	enemyAI.SetState (PATROLLING);
	EnemyPatrollingState (enemyShooter_->moveForce).OnExecute (scene, entityId);
  }

}
