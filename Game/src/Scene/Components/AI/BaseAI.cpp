#include "stdafx.h"
#include "BaseAI.h"
#include "../../Scene.h"
#include "../Transform/Transform.h"
#include "StateMachine/BaseState.h"

void BaseAI::SetState (const AIState &newState)
{
  previousState_ = currentState_;
  //OnExit (currentState_);

  currentState_ = newState;
  //OnEnter (currentState_);
}

const AIState &BaseAI::GetCurrentStateType() const
{
  return currentState_;
}
void BaseAI::RevertState ()
{
  SetState (previousState_);
}

bool BaseAI::IsInState (const AIState &state)
{
  return currentState_ == state;
}