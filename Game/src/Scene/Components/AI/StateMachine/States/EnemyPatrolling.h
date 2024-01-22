#pragma once
#include "../BaseState.h"

class EnemyPatrollingState : public BaseState
{
  private:
  
	  float dashForce_;
  public:
  
	  EnemyPatrollingState(const float &dashForce_);
      virtual void OnExecute (Scene &scene, const int &entityId) override;
};
