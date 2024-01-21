#pragma once
#include "../GameObject.h"

class Scene;
class Vector3;

class Bullet : public GameObject
{
  private:
  
	  int maxLifetime_;
  public:
  
      int speed;
	  int lifetime;

	  static Bullet &InstantiateInScene (Scene &scene, Vector3 position, Vector3 direction);

	  Bullet(int speed = 10, int lifetime = 200);
};
