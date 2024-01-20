#pragma once
#include "../GameObject.h"
#include "../../../Math/Vector3/Vector3.h"

class Scene;

class Player : public GameObject
{
  public:
	float speed;
	float fireRate;
    float fireCoolDown;

	//Shoot
	float shootPower;
    float maxPower;
    float chargeRate;
    int chargeBarId;

	float drag;
    Vector3 velocity;

	 static Player &InstantiateInScene (Scene &scene);

	 Player();

	 void StartFireCooldown();
};
