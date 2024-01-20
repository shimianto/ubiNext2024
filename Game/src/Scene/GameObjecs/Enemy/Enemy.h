#pragma once
#include "../GameObject.h"

class Scene;
class Vector3;

class Enemy : public GameObject
{
  public:
  
	 static Enemy &InstantiateInScene (Scene &scene, Vector3 position);

	  using GameObject::GameObject;
};
