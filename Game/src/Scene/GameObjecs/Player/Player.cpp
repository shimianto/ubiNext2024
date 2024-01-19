#include "stdafx.h"
#include "Player.h"
#include "../../Scene.h"

float Player::speed = 2;

int Player::Init (Scene &scene)
{
  scenId_ = scene.InstantiateNewEntity();
  scene.components.GetMeshFromID (scenId_).LoadTrianglesFromObjectFile ("./data/cube3d.obj");
  scene.components.GetTransformFromID (scenId_).scale = Vector3 (0.1f, 0.1f, 0.1f);

  scene.SetPlayer(*this);
  return scenId_;
}
