#pragma once
class Scene;
class Vector3;
class Transform;
class Physics;

namespace Systems
{
	void SetMainScene (Scene &scene);
	void SetMenuScene (Scene &scene);

	void ChargePlayer (Scene &scene);
	void ShootPlayer (Scene &scene, const float &deltaTime);
    void RotatePlayer (Scene &scene, const Vector3 &rotation);
	
    void ShootBullet (Scene &scene, Transform &enemyTransform, Transform &playerTransf);


    void CheckCollisions (Scene &scene);

    void UpdatePlayer (Scene &scene, const float &deltaTime);
    void UpdateBullets (Scene &scene, const float &deltaTime);
    void UpdateEnemies (Scene &scene, const float &deltaTime);
    void UpdateEnemyShooters (Scene &scene, const float &deltaTime);

    void ExecuteEntityPhysics (Transform &entityTransform, Physics &entityPhysics, const float &deltaTime);
};
