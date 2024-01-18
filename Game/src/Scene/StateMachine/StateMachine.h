#pragma once
#include <vector>
#include <map>
#include "State.h"

class Scene;

template <class T>
class StateMachine
{
  private:
  
	  std::map<StateType, State<T>> states_;
      State<T> currentState_;
      State<T> previousState_;

  public:

    
      void ChangeState (StateType stateType, const int &id, Scene &scene)
      {
	    State<T> newState = states_[stateType];

	    previousState_ = currentState_;
	    currentState_.OnExit(id, scene);

	    currentState_ = newState;
	    currentState_.OnEnter (id, scene);
      }

      void RevertState (const int &id, Scene &scene)
      {
	    ChangeState (previousState_, id, scene);
      }

      bool IsInState(StateType type)
      {
	    return currentState_.type == type;
      }

      void Update (const int &id, Scene &scene)
      {
	    currentState_.OnExecute (id, scene);
      }
};
