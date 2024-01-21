#pragma once
class Scene;

enum AIState
{
	IDLE,
	PATROLLING,
	SHOOTING,
};

class State
{
	public:
    AIState aiState;
    virtual void execute() = 0;
};

class BaseAI
{
  private:
	AIState currentState_;
	AIState previousState_;

	State *stateMachine;

  public:
    void SetState (const AIState &newState);
    
	
	const AIState &GetCurrentStateType () const;


	void RevertState ();

	bool IsInState (const AIState &state);
};

// TODO: Implement BaseState class and populate StateMachine with custom state classes