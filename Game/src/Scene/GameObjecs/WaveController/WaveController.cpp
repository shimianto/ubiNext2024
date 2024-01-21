#include "stdafx.h"
#include "WaveController.h"
#include "../../Scene.h"
#include "../../../Math/Utils/Utils.h"
#include <algorithm>

WaveController::WaveController() : waveNum_(0)
{
}

void WaveController::Init (Scene &scene, int numEnemyStart, int numEnemyShooterStart, int maxEnemies, int maxEnemyShooters, int enemiesIncrement)
{
  this->numEnemyStart = numEnemyStart;
  this->numEnemyShooterStart = numEnemyShooterStart;
  this->maxEnemies = maxEnemies;
  this->maxEnemyShooters = maxEnemyShooters;
  this->enemiesIncrement = enemiesIncrement;

  scene.GetEnemies().SetPooSize (maxEnemies);
  scene.GetEnemyShooters().SetPooSize (maxEnemyShooters);
}

bool WaveController::IsWaveDone (Scene &scene)
{
  return scene.GetEnemies().GetInUseElements().size() == 0;
}

void WaveController::StartNextWave (Scene &scene)
{
  for (int i = 0; i < numEnemyStart + (waveNum_ * enemiesIncrement) && i < maxEnemies; i++) {
	Enemy::InstantiateInScene (scene, 
		Vector3 (
			Utils::RandInt (Physics::ENVIRONMENT_LOWER_BOUDS.x, Physics::ENVIRONMENT_UPPER_BOUDS.x), 
			Utils::RandInt (-20, 20), 
			0
		)
	);
  }

  if (waveNum_ == 1) {
	EnemyShooter::InstantiateInScene (scene, Vector3 (-35, 25, 0), Vector3 (0, 0, 0.6f));
  }
	
  if (waveNum_ == 2) {
	EnemyShooter::InstantiateInScene (scene, Vector3 (35, 25, 0), Vector3 (0, 0, -0.6f));
  }

  waveNum_++;
}
