#include "stdafx.h"
#include "Systems.h"
#include "../../Graphics3D/Camera/Camera.h"
#include "../Scene.h"


void Systems::SetMainScene(Scene &scene)
{
  Camera::mainCamera.transform = Transform();

  int newEntityId = scene.InstantiateNewEntity();
  scene.components.GetMeshFromID (newEntityId).LoadTrianglesFromObjectFile (".\\TestData\\mountains.obj");
}
void Systems::SetMenuScene (Scene &scene)
{
  int newEntityId = scene.InstantiateNewEntity();
  scene.components.GetMeshFromID (newEntityId).LoadTrianglesFromObjectFile (".\\TestData\\teapot.obj");
  scene.components.GetAIFromID (newEntityId).SetState(PATROLLING);
}

int Systems::RandInt (int min, int max)
{
  return rand() % (max - min + 1) + min;
}
float Systems::RandFloat()
{
  return (float)rand() / (float)RAND_MAX;
}
