#include "stdafx.h"
#include "Player.h"
#include "../../Scene.h"


Player &Player::InstantiateInScene (Scene &scene)
{
  Player newPlayer;

  newPlayer.scenId_ = scene.InstantiateNewEntity();
  scene.components.GetMeshFromID (newPlayer.scenId_).LoadTrianglesFromObjectFile ("./data/cone3d.obj");
  scene.components.GetTransformFromID (newPlayer.scenId_).scale = Vector3 (0.06f, 0.06f, 0.06f);
  scene.components.GetColliderFromID (newPlayer.scenId_).radius = 2;

  scene.SetPlayer (newPlayer);

  return scene.GetPlayer();
}

Player::Player() : 
	GameObject(), speed (2), fireRate (50), fireCoolDown (0), 
	shootPower (0), maxPower (10), chargeRate (0.2f), drag (0.1f), velocity (Vector3())
{
}

void Player::StartFireCooldown()
{
  fireCoolDown = fireRate;
}
