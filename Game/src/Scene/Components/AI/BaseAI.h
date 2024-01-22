#pragma once
#include <map>
#include "StateMachine/BaseState.h"

class Scene;

class BaseAI
{
  private:
	AIState currentState_;
	AIState previousState_;


  public:
    
		
	  const AIState &GetCurrentStateType () const;
	  
	  void SetState (const AIState &newState);
	  void RevertState ();
	  bool IsInState (const AIState &state);
};

// TODO: Implement BaseState class and populate StateMachine with custom state classes