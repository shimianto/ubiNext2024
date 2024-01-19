#include "stdafx.h"
#include "Player.h"
#include "../../Scene.h"


Player &Player::InstantiateInScene (Scene &scene)
{
  Player newPlayer;

  newPlayer.scenId_ = scene.InstantiateNewEntity();
  scene.components.GetMeshFromID (newPlayer.scenId_).LoadTrianglesFromObjectFile ("./data/cube3d.obj");
  scene.components.GetTransformFromID (newPlayer.scenId_).scale = Vector3 (0.1f, 0.1f, 0.1f);

  scene.SetPlayer (newPlayer);

  return scene.GetPlayer();
}

Player::Player() : GameObject(), 
	speed (2), fireRate (50), fireCoolDown(0)
{
}

int Player::Init (Scene &scene)
{
  
  return scenId_;
}

void Player::StartFireCooldown()
{
  fireCoolDown = fireRate;
}
