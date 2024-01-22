#pragma once
class Scene;

enum AIState
{
  IDLE,
  PATROLLING,
  SHOOTING,
};

class BaseState
{
  public:
  AIState aiState;
  virtual void OnExecute(Scene &scene, const int &entityId) = 0;
};
