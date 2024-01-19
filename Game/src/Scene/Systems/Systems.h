#pragma once
#include"../Scene.h"

namespace Systems
{
	void SetMainScene (Scene &scene);
	void SetMenuScene (Scene &scene);

	void MovePlayer (Scene &scene, const Vector3 &movement);
    void ShootBullet (Scene &scene);
	void UpdateEnemies(Scene &scene);
	
	int RandInt (int min, int max);
	float RandFloat();
};
