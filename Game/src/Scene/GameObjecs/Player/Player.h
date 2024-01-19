#pragma once
#include "../GameObject.h"

class Scene;

class Player : public GameObject
{
  public:
	float speed;
	float fireRate;
    float fireCoolDown;

	 static Player &InstantiateInScene (Scene &scene);

	 Player();

	 int Init (Scene &scene) override;
	 void StartFireCooldown();
};
