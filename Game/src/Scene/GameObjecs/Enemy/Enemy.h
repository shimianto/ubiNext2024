#pragma once
#include "../GameObject.h"

class Scene;

class Enemy : public GameObject
{
  public:
  
	  using GameObject::GameObject;

	  int Init (Scene &scene) override;
};
