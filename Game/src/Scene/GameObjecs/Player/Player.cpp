#include "stdafx.h"
#include "Player.h"
#include "../../Scene.h"

float Player::speed = 2;

int Player::Init (Scene &scene)
{
  int id = scene.InstantiateNewEntity();
  scene.components.GetMeshFromID (id).LoadTrianglesFromObjectFile ("./data/cube3d.obj");
  scene.components.GetTransformFromID (id).scale = Vector3 (0.1f, 0.1f, 0.1f);

  scene.playerId = id;

  return id;
}
