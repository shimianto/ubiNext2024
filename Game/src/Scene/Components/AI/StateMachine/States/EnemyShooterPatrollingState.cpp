#include "stdafx.h"
#include "EnemyShooterPatrollingState.h"
#include "../../../../Scene.h"
#include "../../../../../Math/Utils/Utils.h"

void EnemyShooterPatrollingState::OnExecute (Scene &scene, const int &entityId)
{
  if (scene.components.GetPhysicsFromID (entityId).velocity == Vector3() && Utils::RandFloat() > 0.3) {
	scene.components.GetAIFromID (entityId).SetState (SHOOTING);
  } else {
	EnemyPatrollingState::OnExecute (scene, entityId);
  }
}
