#include "stdafx.h"
#include "Player.h"
#include "../../Scene.h"
#include "../../Managers/UIManager/UIManager.h"

Player &Player::InstantiateInScene (Scene &scene)
{
  Player newPlayer;

  newPlayer.scenId_ = scene.InstantiateNewEntity();
  scene.components.GetMeshFromID (newPlayer.scenId_).LoadTrianglesFromObjectFile ("./data/cone3d.obj");
  scene.components.GetTransformFromID (newPlayer.scenId_).scale = Vector3 (0.06f, 0.06f, 0.06f);
  scene.components.GetColliderFromID (newPlayer.scenId_).radius = 2;

  Physics &playerPhysics = scene.components.GetPhysicsFromID (newPlayer.scenId_);
  playerPhysics.gravity = true;
  playerPhysics.drag = 0.05f;

  UIBar chargeBar(Vector3 ((float)APP_VIRTUAL_WIDTH - 320, 20), Vector3 (300, 80), 0);
  newPlayer.chargeBarId = scene.uiManager_->GetActiveUI (scene).InsertNewBar (chargeBar);


  scene.SetPlayer (newPlayer);

  return scene.GetPlayer();
}

Player::Player() : 
	GameObject(),
	shootPower (0), maxPower (100), chargeRate (0.4f), chargeBarId(-1)
{
}
