#pragma once
#include "../BaseState.h"
#include "../../../../GameObjecs/EnemyShooter/EnemyShooter.h"

class EnemyShooterAttackState :public BaseState
{
  private:
  EnemyShooter *enemyShooter_;

  public:
  EnemyShooterAttackState (EnemyShooter *enemyShooter);
  virtual void OnExecute (Scene & scene, const int &entityId) override;
  
};
