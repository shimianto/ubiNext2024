#pragma once
#include "../GameObject.h"

class Scene;

class Player : public GameObject
{
  public:
	//Shoot
	float shootForce;
    float maxPower;
    float chargeRate;
    int chargeBarId;


	 static Player &InstantiateInScene (Scene &scene);

	 Player();
};
