#include "stdafx.h"
#include "Systems.h"
#include "../Scene.h"
#include "../GameObjecs/Enemy/Enemy.h"
#include "../GameObjecs/Player/Player.h"
#include "../Managers/UIManager/UIManager.h"
#include "../Managers/AudioManager/AudioManager.h"
#include "../../Graphics3D/Camera/Camera.h"
#include "../../Math/Vector3/Vector3.h"
#include "../../Math/Utils/Utils.h"
#include "../Components/AI/StateMachine/States/EnemyPatrolling.h"


void Systems::SetUpMainScene(Scene &scene)
{
  Camera::mainCamera.transform = Transform();

  UI mainGameUI;
  scene.uiManager_->RegisterUI (MAIN_SCENE, mainGameUI);

  Player::InstantiateInScene (scene);
  scene.waveController.Init(scene, 1, 0, 10, 3, 1);
  scene.waveController.StartNextWave (scene);
}
void Systems::SetUpMenuScene (Scene &scene)
{
  Camera::mainCamera.transform = Transform();

  UI menuUI;

  //menuUI.InsertNewBar (UIBar (Vector3 (0, 500), Vector3 (APP_VIRTUAL_WIDTH, 300), 1, Color ()));

  menuUI.InsertNewText (UIText (Vector3 (450, 600), "Hit here to play", Color(), GLUT_BITMAP_9_BY_15));

  menuUI.InsertNewText (UIText (Vector3 (20, 470), "Space / Right trigger to charge", Color(), GLUT_BITMAP_9_BY_15));
  menuUI.InsertNewText (UIText (Vector3 (20, 450), "Release to shoot", Color(), GLUT_BITMAP_9_BY_15));
  menuUI.InsertNewText (UIText (Vector3 (20, 400), "A&D / Left stick to aim", Color(), GLUT_BITMAP_9_BY_15));

  menuUI.InsertNewText (UIText (Vector3 (750, 450), "Hit all blue for next wave", Color(), GLUT_BITMAP_9_BY_15));
  menuUI.InsertNewText (UIText (Vector3 (750, 400), "Avoid red and pink", Color(), GLUT_BITMAP_9_BY_15));
  menuUI.InsertNewText (UIText (Vector3 (750, 350), "Have fun! :)", Color(), GLUT_BITMAP_9_BY_15));

  scene.uiManager_->RegisterUI (MENU_SCENE, menuUI);

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

void Systems::TryDamageToPlayer (Player &player, Health &pHealth)
{
  if (player.isHit && player.hitCooldown == 0) {
	pHealth.TakeDamage (1);
	App::PlaySound (AudioManager::PLAYER_DMG_SFX);
	player.hitCooldown = player.maxCooldown;
  } else if (player.hitCooldown > 0) {
	player.hitCooldown--;
	player.isHit = player.hitCooldown != 0;
  }
}

void Systems::ExecuteEnemyAI (Scene &scene, Enemy *enemy)
{
  BaseAI &enemyAI = scene.components.GetAIFromID (enemy->GetSceneId());

  switch (enemyAI.GetCurrentStateType()) {
  case PATROLLING:
	EnemyPatrolling (enemy->moveForce).OnExecute(scene, enemy->GetSceneId());
	break;
  default:
	break;
  }
}

void Systems::ExecuteEnemyShooterAI (Scene &scene, EnemyShooter &enemy)
{
  Player &player = scene.GetPlayer();

  if (player.GetSceneId() == -1) {
	return;
  }

  Transform &playerTransf = scene.components.GetTransformFromID (player.GetSceneId());

  Transform &enemyTransform = scene.components.GetTransformFromID (enemy.GetSceneId());
  BaseAI &enemyAI = scene.components.GetAIFromID (enemy.GetSceneId());


  //Run AI
  switch (IDLE) {
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
