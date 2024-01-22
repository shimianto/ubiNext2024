#pragma once
#include "EnemyPatrolling.h"

class EnemyShooterPatrollingState : public EnemyPatrollingState
{
  public:
	  
	  using EnemyPatrollingState::EnemyPatrollingState;
 
	  virtual void OnExecute (Scene &scene, const int &entityId) override;
};
