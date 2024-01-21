#include "stdafx.h"
#include "Button.h"
#include "../../Scene.h"
#include "../../../Math/Vector3/Vector3.h"

void Button::InstantiateInScene (Scene &scene, Vector3 position)
{
  int poolId = scene.GetButtons().InstantiateNextAvailable();

  if (poolId == -1) {
	return;
  }

  Button &newBtn = scene.GetButtons().GetElementByID (poolId);
  newBtn.poolId_ = poolId;

  if (newBtn.scenId_ == -1) {
	newBtn.scenId_ = scene.InstantiateNewEntity();
	Mesh &mesh = scene.components.GetMeshFromID (newBtn.scenId_);
	mesh.LoadTrianglesFromObjectFile ("./data/sphere3d.obj");
	mesh.col = Color (0, 0, 1, 0);

	scene.components.GetTransformFromID (newBtn.scenId_).scale = Vector3 (0.065f, 0.065f, 0.065f);
	scene.components.GetColliderFromID (newBtn.scenId_).radius = 2;

  } else {
	scene.EnableEntity (newBtn.scenId_);
  }
  scene.components.GetTransformFromID (newBtn.scenId_).position = position;
}
