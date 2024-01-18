#pragma once

class Scene;


enum StateType
{
    PATROLLING,
    CHASING,
    ATTACKING
};

template <class T> class State
{
  public:
  
      StateType type;
	  virtual void OnEnter (const int &id, Scene &scene) = 0;
      virtual void OnExecute (const int &id, Scene &scene) = 0;
      virtual void OnExit (const int &id, Scene &scene) = 0;
};