#pragma once
class Scene;

class GameObject
{
  protected:
  
	  int scenId_;
      int poolId_;

  public:
  
      GameObject()
          : scenId_ (-1), poolId_(-1)
          {}

      virtual const int GetSceneId()
      {
	    return scenId_;
      }
};
