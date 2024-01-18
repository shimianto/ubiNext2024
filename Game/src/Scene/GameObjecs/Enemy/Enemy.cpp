#include "stdafx.h"
#include "Enemy.h"
#include "../../Scene.h"

int Enemy::Init (Scene &scene)
{
  int id = scene.InstantiateNewEntity();
  scene.components.GetMeshFromID (id).LoadTrianglesFromObjectFile (".\\TestData\\teapot.obj");
  scene.components.GetAIFromID (id).SetState (PATROLLING);

  scene.enemyObjs.insert (id);

  return id;
}