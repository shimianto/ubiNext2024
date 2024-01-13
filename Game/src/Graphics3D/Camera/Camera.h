#pragma once
#include "../../Math/Vector3/Vector3.h"
#include "../../Math/Matrix/Matrix.h"

class Camera
{
  private:
  Matrix viewMat, invViewMat;
  public:
  static Camera mainCamera;

  Vector3 pos, target, up;

  Camera();
	
  void UpdateViewMatrices();

  Matrix GetInvViewMatrix() const;
  Matrix GetViewMatrix() const;

};
