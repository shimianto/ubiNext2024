#pragma once
#include "../GameObject.h"

class Scene;
class Vector3;

class Enemy : public GameObject
{
  public:
	  float moveForce;

      static void InstantiateInScene (Scene &scene, Vector3 position);

	  Enemy();
};
