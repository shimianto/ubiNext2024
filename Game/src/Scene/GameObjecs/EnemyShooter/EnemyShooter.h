#pragma once
#include "../GameObject.h"

class Scene;
class Vector3;

class EnemyShooter : public GameObject
{
      float shootCooldown_;
  public:
  
      float coolDownTimer;
      float projectileForce;

  static EnemyShooter &InstantiateInScene (Scene &scene, Vector3 position, Vector3 rotation);

  EnemyShooter();
  void ResetCooldown();
};
