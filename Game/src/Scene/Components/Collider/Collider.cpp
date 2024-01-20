#include "stdafx.h"
#include "Collider.h"
#include "../../../Math/Vector3/Vector3.h"
#include "../../Scene.h"
#include "../../../Math/Utils/Utils.h"

bool Collider::CheckCollision (Scene &scene, const int &obj1Id, const int &obj2Id)
{
  Vector3 p1 = scene.components.GetTransformFromID (obj1Id).position;
  Vector3 p2 = scene.components.GetTransformFromID (obj2Id).position;

  Collider c1 = scene.components.GetColliderFromID (obj1Id);
  Collider c2 = scene.components.GetColliderFromID (obj2Id);

  return Utils::GetDistance (p1, p2) < c1.radius + c2.radius;

}
