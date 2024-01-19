#pragma once
#include "../GameObject.h"

class Bullet : public GameObject
{
  public:
  
	  using GameObject::GameObject;
  
	  int Init (Scene &scene) override;
};
