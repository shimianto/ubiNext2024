#pragma once
#include "../BaseState.h"

class EnemyPatrolling : public BaseState
{
  private:
  
	  float dashForce_;
  public:
  
	  EnemyPatrolling(const float &dashForce_);
      virtual void OnExecute (Scene &scene, const int &entityId) override;
};
