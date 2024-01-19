#pragma once
#include "../GameObject.h"

class Bullet : public GameObject
{
  private:
  
	  int maxLifetime_;
  public:
  
      int speed;
	  int lifetime;

	  static Bullet &InstantiateInScene (Scene &scene);

	  Bullet(int speed = 5, int lifetime = 100);
	  int Init (Scene &scene) override;
};
