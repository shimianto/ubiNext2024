#pragma once
#include "../../Math/Vector3/Vector3.h"
#include "../../Math/Matrix/Matrix.h"

class Camera
{
  public:
  static Camera mainCamera;

  Vector3 target;
  Transform transform;

  Camera();
};
