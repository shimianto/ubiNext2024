#pragma once
class Scene;

enum AIState
{
	IDLE,
	PATROLLING,
	SHOOTING,
};

class BaseAI
{
  private:
	AIState currentState_;
	AIState previousState_;

  public:
    void SetState (const AIState &newState);
    const AIState &GetState () const;

	void RevertState ();

	bool IsInState (const AIState &state);
};

// TODO: Implement BaseState class and populate StateMachine with custom state classes