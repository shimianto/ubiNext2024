#pragma once
class Scene;
class Vector3;

namespace Systems
{
	void SetMainScene (Scene &scene);
	void SetMenuScene (Scene &scene);

	void ChargePlayer (Scene &scene);
	void MovePlayer (Scene &scene, const float &deltaTime);
    void RotatePlayer (Scene &scene, const Vector3 &rotation);
    void ShootBullet (Scene &scene);

	void CheckCollisions (Scene &scene);

    void UpdatePlayer (Scene &scene, const float &deltaTime);
    void UpdateBullets (Scene &scene);
	void UpdateEnemies(Scene &scene);
	
};
