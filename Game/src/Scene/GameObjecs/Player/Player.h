#pragma once
#include "../GameObject.h"

class Scene;

class Player : public GameObject
{
  public:
	  using GameObject::GameObject;

	static float speed;
	int Init (Scene &scene) override;
};
