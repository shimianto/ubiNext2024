#include "stdafx.h"
#include "Systems.h"
#include "../../Graphics3D/Camera/Camera.h"
#include "../Scene.h"
#include "../Managers/UIManager/UIManager.h"
#include "../GameObjecs/Enemy/Enemy.h"
#include "../GameObjecs/Player/Player.h"
#include "../../Math/Vector3/Vector3.h"
#include "../../Math/Utils/Utils.h"
#include "../Managers/AudioManager/AudioManager.h"
#include <functional>
#include <cmath>


void Systems::SetUpMainScene(Scene &scene)
{
  Camera::mainCamera.transform = Transform();

  //Camera::mainCamera.transform.position = Vector3 (-6.18, 7.38, -6.72);
  //Camera::mainCamera.transform.rotation = Vector3 (0, -0.42, 0); 
  
  //int newEntityId = scene.InstantiateNewEntity();
  //scene.components.GetMeshFromID (newEntityId).LoadTrianglesFromObjectFile (".\\TestData\\mountains.obj");

  Player::InstantiateInScene (scene);
  scene.waveController.Init(scene, 1, 0, 10, 3, 1);
  scene.waveController.StartNextWave (scene);
}
void Systems::SetUpMenuScene (Scene &scene)
{
  App::PlaySound (AudioManager::MENU_BGM, true);
  Player::InstantiateInScene (scene);
  Button::InstantiateInScene (scene, Vector3 (0, 15));
}
void Systems::SetUpParticleScene (Scene & scene)
{
  scene.InstantiateNewEntity();
  scene.components.GetParticlesFromID (0).mesh.LoadTrianglesFromObjectFile ("./data/cube3d.obj");
}

void Systems::ChargePlayer (Scene &scene)
{
  Player &p = scene.GetPlayer();
  Physics &playerPhysics = scene.components.GetPhysicsFromID (p.GetSceneId());

  if (playerPhysics.velocity == Vector3() && p.moveForce < p.maxPower) {
	p.moveForce += p.chargeRate;

	if (!App::IsSoundPlaying (AudioManager::PLAYER_CHARGING_SFX)) {
	  App::PlaySound (AudioManager::PLAYER_CHARGING_SFX, true);
	}
  }
}

void Systems::ShootPlayer (Scene &scene, const float &deltaTime)
{
  Player &p = scene.GetPlayer();
  Physics &playerPhysics = scene.components.GetPhysicsFromID (p.GetSceneId());


  if (p.moveForce > 0 && playerPhysics.velocity == Vector3()) {
	Transform &playerTransform = scene.components.GetTransformFromID (p.GetSceneId());
	ParticleSystem &playerParticles = scene.components.GetParticlesFromID (p.GetSceneId());

	Matrix matRot = Matrix::MakeRotationMatrix (playerTransform.rotation);

	// Calculate new forward direction
	Vector3 vForward = ((Vector3 (0, 1, 0)) * matRot).Normalize();
	vForward.z = 0;

	playerPhysics.velocity = vForward * p.moveForce;
	p.moveForce = 0;

	playerParticles.SpawnParticles (5, playerTransform.position, vForward*-1);

	App::StopSound (AudioManager::PLAYER_CHARGING_SFX);
	App::PlaySound (AudioManager::PLAYER_DASH_SFX);
  }

}

void Systems::RotatePlayer (Scene &scene, const Vector3 &rotation)
{
	Transform &playerTransform = scene.components.GetTransformFromID (scene.GetPlayer().GetSceneId());
	playerTransform.rotation.z += rotation.x;
}

void Systems::UpdatePlayer (Scene &scene, const float &deltaTime)
{
  Player &player = scene.GetPlayer();

  if (player.GetSceneId() == -1) {
	return;
  }

  Transform &playerTransform = scene.components.GetTransformFromID (player.GetSceneId());
  Physics &playerPhysics = scene.components.GetPhysicsFromID (player.GetSceneId());

  UIBar &chargeBar = scene.uiManager_->GetActiveUI (scene).GetBarFromId (player.chargeBarId);
  chargeBar.fill = (player.moveForce / player.maxPower);
  chargeBar.fill = chargeBar.fill > 1 ? 1 : chargeBar.fill;
  chargeBar.color = Color (chargeBar.fill, 1 - chargeBar.fill, 0);

  scene.uiManager_->GetActiveUI (scene).UpdateBarFromId (player.chargeBarId, chargeBar);

  ExecuteEntityPhysics (playerTransform, playerPhysics, deltaTime);

  //Check if was hit by projectile
  if (player.isHit && player.hitCooldown == 0) {
	Health &pHealth = scene.components.GetHealthFromID (player.GetSceneId());
	pHealth.TakeDamage (1);
	App::PlaySound (AudioManager::PLAYER_DMG_SFX);
	if (pHealth.GetValue() <= 0) {
	  scene.SetScene (MENU_SCENE);
	}


	UIBar &healthBar = scene.uiManager_->GetActiveUI (scene).GetBarFromId (player.healthBarId);
	healthBar.fill = (float)pHealth.GetValue() / (float)pHealth.GetMax();

	scene.uiManager_->GetActiveUI (scene).UpdateBarFromId (player.healthBarId, healthBar);


	player.hitCooldown = player.maxCooldown;
  } else if(player.hitCooldown > 0) {
	player.hitCooldown--;
	player.isHit = player.hitCooldown != 0;
  }
}

void Systems::UpdateEnemies (Scene &scene, const float &deltaTime)
{
  Player &player = scene.GetPlayer();

  if (player.GetSceneId() == -1) {
	return;
  }

  Pool<Enemy> &enemyPool = scene.GetEnemies();
  std::vector<Enemy> enemiesHit;

  for (const auto &poolId : enemyPool.GetInUseElements()) {
	Enemy &enemy = enemyPool.GetElementByID (poolId);
	Transform &enemyTransform = scene.components.GetTransformFromID (enemy.GetSceneId());
	Physics &enemyPhysics = scene.components.GetPhysicsFromID (enemy.GetSceneId());
	BaseAI &enemyAI = scene.components.GetAIFromID (enemy.GetSceneId());
	
	ParticleSystem &entityParticles = scene.components.GetParticlesFromID (enemy.GetSceneId());
	Mesh &entityMesh = scene.components.GetMeshFromID (enemy.GetSceneId());

	ExecuteEntityPhysics (enemyTransform, enemyPhysics, deltaTime);

	//Run AI
	switch (enemyAI.GetState()) {
	case PATROLLING:
	  if (enemyPhysics.velocity == Vector3()) {
		enemyPhysics.velocity = Vector3 (Utils::RandInt (-2, 2), Utils::RandInt (-2, 2)) * enemy.moveForce;
		
		entityParticles.SpawnParticles (5, enemyTransform.position - enemyPhysics.velocity.Normalize() * 2, (enemyPhysics.velocity.Normalize() * -1)/2, entityMesh.col);
		
		if (!App::IsSoundPlaying (AudioManager::ENEMY_DASH_SFX)) {
			App::PlaySound (AudioManager::ENEMY_DASH_SFX);
		}
	  }
	  break;
	default:
	  break;
	}

	//Check Collisions
	if (Collider::CheckCollision (scene, player.GetSceneId(), enemy.GetSceneId())) {
	  enemiesHit.push_back (enemy);
	} 
  }

  //Disabled hit
  for (auto &e : enemiesHit) {
	DisableGameObjectInScene (scene, &e, &enemyPool);
  }

  //Try new wave
  if (scene.waveController.IsWaveDone (scene)) {
	scene.waveController.StartNextWave (scene);
  }
}

void Systems::UpdateEnemyShooters (Scene &scene, const float &deltaTime)
{
  Player &player = scene.GetPlayer();
  
  if (player.GetSceneId() == -1) {
	return;
  }

  Transform &playerTransf = scene.components.GetTransformFromID (player.GetSceneId());

  Pool<EnemyShooter> &enemyShootersPool = scene.GetEnemyShooters();
  
  for (auto &poolId	: enemyShootersPool.GetInUseElements()) {
	EnemyShooter &enemy = enemyShootersPool.GetElementByID (poolId);
	Transform &enemyTransform = scene.components.GetTransformFromID (enemy.GetSceneId());
	BaseAI &enemyAI = scene.components.GetAIFromID (enemy.GetSceneId());
	
	enemy.coolDownTimer -= 1;

	//Run AI
	switch (enemyAI.GetState()) {
	case SHOOTING:
	  if (enemy.coolDownTimer <= 0) {
		ShootBullet (scene, enemyTransform, playerTransf);
		enemy.ResetCooldown();
	  }
	  break;
	default:
	  break;
	}
  }
}

void Systems::ShootBullet (Scene &scene, Transform &enemyTransform, Transform &playerTransf)
{
  Vector3 spawn = enemyTransform.position;
  Vector3 direction = (playerTransf.position - enemyTransform.position);
  direction.z = 0;

  Bullet::InstantiateInScene (scene, spawn, direction);
  App::PlaySound (AudioManager::ENEMY_SHOOT_SFX);
}

void Systems::UpdateBullets (Scene &scene, const float &deltaTime)
{
  Player &player = scene.GetPlayer();

  if (player.GetSceneId() == -1) {
	return;
  }

  Pool<Bullet> &bulletPool = scene.GetBullets();
  std::vector<Bullet> bulletsToDiable;

  for (auto &bulletId : bulletPool.GetInUseElements())
  {
	Bullet &b = bulletPool.GetElementByID (bulletId);

	b.lifetime--;

	if (b.lifetime <= 0) {
	  bulletsToDiable.push_back (b);
	  continue;
	}
	Transform &transf = scene.components.GetTransformFromID (b.GetSceneId());
	Physics &phys = scene.components.GetPhysicsFromID (b.GetSceneId());
	ParticleSystem &entityParticles = scene.components.GetParticlesFromID (b.GetSceneId());
	Mesh &entityMesh = scene.components.GetMeshFromID (b.GetSceneId());

	ExecuteEntityPhysics (transf, phys, deltaTime);
	entityParticles.SpawnParticles (1, transf.position - phys.velocity.Normalize()*2, (phys.velocity.Normalize() * -1) / 2, entityMesh.col);


	//Check Collisions
	if (!player.isHit && Collider::CheckCollision (scene, player.GetSceneId(), b.GetSceneId())) {
	  bulletsToDiable.push_back (b);
	  player.isHit = true;
	} 
  }

  //Disabled hit
  for (auto &bullet : bulletsToDiable) {
	DisableGameObjectInScene (scene, &bullet, &bulletPool);
  }
}

void Systems::ExecuteEntityPhysics (Transform &entityTransform, Physics &entityPhysics, const float &deltaTime)
{

  //Update pos
  entityTransform.position += entityPhysics.velocity / deltaTime;

  //Bounce on boundaries
  ExecuteOutOfBoundsPhysics (entityTransform, entityPhysics);

  //Gravity
  if (entityPhysics.gravity) {
	if (entityTransform.position.y > Physics::ENVIRONMENT_LOWER_BOUDS.y + 1) {
	  entityPhysics.velocity.y -= entityPhysics.gravityForce;
	} else {
	  entityPhysics.velocity.x *= 0.6;
	  entityPhysics.velocity.y *= 0.6;
	}
  }

  //Execute drag
  if (entityPhysics.velocity.x != 0) {
	if (entityPhysics.velocity.x < 0) {
	  entityPhysics.velocity.x += entityPhysics.drag;
	} else {
	  entityPhysics.velocity.x -= entityPhysics.drag;
	}
  }
  if (entityPhysics.velocity.y != 0) {
	if (entityPhysics.velocity.y < 0) {
	  entityPhysics.velocity.y += entityPhysics.drag;
	} else {
	  entityPhysics.velocity.y -= entityPhysics.drag;
	}
  }


  //Set vel to zero if within variance
  if (entityPhysics.velocity.x <= entityPhysics.drag && entityPhysics.velocity.x >= -entityPhysics.drag) {
	entityPhysics.velocity.x = 0;
  }
  if (entityPhysics.velocity.y <= entityPhysics.drag && entityPhysics.velocity.y >= -entityPhysics.drag) {
	entityPhysics.velocity.y = 0;
  }
}

void Systems::ExecuteOutOfBoundsPhysics (Transform &entityTransform, Physics &entityPhysics)
{
  bool hitLowerXBound = entityTransform.position.x < Physics::ENVIRONMENT_LOWER_BOUDS.x;
  bool hitUpperXBound = entityTransform.position.x > Physics::ENVIRONMENT_UPPER_BOUDS.x;
  bool hitLowerYBound = entityTransform.position.y < Physics::ENVIRONMENT_LOWER_BOUDS.y;
  bool hitUpperYBound = entityTransform.position.y > Physics::ENVIRONMENT_UPPER_BOUDS.y;

  if (hitLowerXBound) {
	entityPhysics.velocity.x *= -1;
	entityTransform.position.x = Physics::ENVIRONMENT_LOWER_BOUDS.x;
  } else if (hitUpperXBound) {
	entityPhysics.velocity.x *= -1;
	entityTransform.position.x = Physics::ENVIRONMENT_UPPER_BOUDS.x;
  }
  if (hitLowerYBound) {
	entityPhysics.velocity.y *= -1;
	entityTransform.position.y = Physics::ENVIRONMENT_LOWER_BOUDS.y;
  } else if (hitUpperYBound) {
	entityPhysics.velocity.y *= -1;
	entityTransform.position.y = Physics::ENVIRONMENT_UPPER_BOUDS.y;
  }

  if (entityPhysics.bounceSFX && (hitLowerXBound || hitLowerYBound || hitUpperXBound || hitUpperYBound)) {
	App::PlaySound (AudioManager::ENTITY_BOUNCE_SFX);
  }

}
