#include "stdafx.h"
#include "BaseAI.h"
#include "../../Scene.h"
#include "../Transform/Transform.h"

void BaseAI::SetState (const AIState &newState)
{
  previousState_ = currentState_;
  //OnExit (currentState_);

  currentState_ = newState;
  //OnEnter (currentState_);
}

void BaseAI::Update (const int &id, Scene &scene)
{
  switch (currentState_) {
  case PATROLLING:
	ExecutePatrollingState (scene, id);
	break;
  default:
	break;
  }
}

void BaseAI::ExecutePatrollingState (Scene &scene, const int &id)
{
  Transform &entTransf = scene.components.GetTransformFromID (id);
  entTransf.rotation.x += 0.005;
  entTransf.rotation.y += 0.005;
}

void BaseAI::RevertState ()
{
  SetState (previousState_);
}

bool BaseAI::IsInState (const AIState &state)
{
  return currentState_ == state;
}