#pragma once
class Scene;
class Vector3;
class Transform;
class Physics;
class Player;
class Enemy;
class EnemyShooter;
class Health;
class Bullet;
class GameObject;
template <class T> class Pool;

namespace Systems
{
	void SetUpMainScene (Scene &scene);
    void SetUpMenuScene (Scene &scene);

	void ChargePlayer (Scene &scene);
	void ShootPlayer (Scene &scene, const float &deltaTime);
    void RotatePlayer (Scene &scene, const Vector3 &rotation);

    void ExecuteEntityPhysics (Transform &entityTransform, Physics &entityPhysics, const float &deltaTime);
    void ExecuteOutOfBoundsPhysics (Transform &entityTransform, Physics &entityPhysics);

    void TryDamageToPlayer (Player &player, Health &pHealth);
    void ShootBullet (Scene &scene, Transform &enemyTransform, Transform &playerTransf);

    void ExecuteEnemyAI (Scene &scene, Enemy *enemy);
    void ExecuteEnemyShooterAI (Scene &scene, EnemyShooter &enemy);
    void ExecuteBulletParticles (Scene &scene, Bullet &b);

    template <class T> void DisableGameObjectInScene (Scene &scene, GameObject * gameObj, Pool<T> *pool)
    {
      scene.DisableEntity (gameObj->GetSceneId());
      pool->DisableElement (gameObj->GetPoolId());
    }
    };
