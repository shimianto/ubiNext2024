#pragma once
class Scene;

enum AIState
{
	IDLE,
	PATROLLING
};

class BaseAI
{
  private:
	AIState currentState_;
	AIState previousState_;

    void ExecutePatrollingState (Scene &scene, const int &id);

  public:
    void SetState (const AIState &newState);

	void Update (const int &id, Scene &scene);

	void RevertState ();

	bool IsInState (const AIState &state);
};
