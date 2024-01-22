#pragma once
#include "../Enemy/Enemy.h"

class Scene;
class Vector3;

class EnemyShooter : public Enemy
{
      float shootCooldown_;
  public:
  
      float coolDownTimer;
      float projectileForce;

  
      static void InstantiateInScene (Scene &scene, Vector3 position, Vector3 rotation);

  EnemyShooter();
  void ResetCooldown();
};
