#include "stdafx.h"
#include "Enemy.h"
#include "../../Scene.h"

int Enemy::Init (Scene &scene)
{
  int id = scene.InstantiateNewEntity();
  scene.components.GetMeshFromID (id).LoadTrianglesFromObjectFile ("./data/cone3d.obj");
  scene.components.GetTransformFromID (id).scale = Vector3 (0.1f, 0.1f, 0.1f);
  scene.components.GetAIFromID (id).SetState (PATROLLING);

  scene.enemyObjs.insert (id);

  return id;
}