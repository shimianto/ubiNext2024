#pragma once
#include "../GameObject.h"

class Scene;

class Player : public GameObject
{
  public:
	//Shoot
	float moveForce;
    float maxPower;
    float chargeRate;
    int chargeBarId;
    int healthBarId;
    
    //Hit
    bool isHit;
    int hitCooldown;
    int maxCooldown;



	 static Player &InstantiateInScene (Scene &scene);

	 Player();
};
