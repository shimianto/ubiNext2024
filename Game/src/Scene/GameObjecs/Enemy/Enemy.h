#pragma once
#include "../GameObject.h"

class Scene;
class Vector3;

class Enemy : public GameObject
{
  public:
	  float shootForce;

	  static Enemy &InstantiateInScene (Scene &scene, Vector3 position);

	  Enemy();
};
