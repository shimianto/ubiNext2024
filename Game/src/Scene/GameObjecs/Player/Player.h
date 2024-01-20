#pragma once
#include "../GameObject.h"

class Scene;

class Player : public GameObject
{
  public:
	//Shoot
	float shootPower;
    float maxPower;
    float chargeRate;
    int chargeBarId;


	 static Player &InstantiateInScene (Scene &scene);

	 Player();
};
