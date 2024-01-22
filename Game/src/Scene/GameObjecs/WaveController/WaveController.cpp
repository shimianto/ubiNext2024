#include "stdafx.h"
#include "WaveController.h"
#include "../../Scene.h"
#include "../../../Math/Utils/Utils.h"
#include <algorithm>

WaveController::WaveController() : waveNum_ (0), isInitialized_(false)
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

  isInitialized_ = true;
}

bool WaveController::IsInitialized()
{
  return isInitialized_;
}

bool WaveController::IsWaveDone (Scene &scene)
{
  return scene.GetEnemies().GetInUseElements().size() == 0 && scene.GetEnemyShooters().GetInUseElements().size() == 0;
}


void WaveController::StartNextWave (Scene &scene)
{
  if (!isInitialized_) {
	return;
  }

  for (int i = 0; i < numEnemyStart + (waveNum_ * enemiesIncrement) && i < maxEnemies; i++) {
	Enemy::InstantiateInScene (scene, 
		Vector3 (
			Utils::RandInt (Physics::ENVIRONMENT_LOWER_BOUDS.x, Physics::ENVIRONMENT_UPPER_BOUDS.x), 
			Utils::RandInt (-20, 20), 
			0
		)
	);
  }
  
  for (int i = 0; i < numEnemyShooterStart + (waveNum_ * enemiesIncrement) && i < maxEnemyShooters; i++) {
		EnemyShooter::InstantiateInScene (
			scene, 
			Vector3 (
				Utils::RandInt (Physics::ENVIRONMENT_LOWER_BOUDS.x, Physics::ENVIRONMENT_UPPER_BOUDS.x), 
				Utils::RandInt (-20, 20), 
				0), 
			Vector3 (0, 0, 0));
  }
  waveNum_++;
}
