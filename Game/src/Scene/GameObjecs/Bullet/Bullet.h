#pragma once
#include "../GameObject.h"

class Bullet : public GameObject
{
  private:
  
	  int maxLifetime_;
  public:
  
	  int lifetime;

	  static Bullet &InstantiateInScene (Scene &scene);

	  Bullet(int lifetime = 100);
	  int Init (Scene &scene) override;
};
