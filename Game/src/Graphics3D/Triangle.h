#pragma once
#include "Vector3.h"

namespace Graphics3D {
class Triangle
{
  public:
  Vector3 vertices[3];

  Triangle (Vector3 v1 = Vector3(), Vector3 v2 = Vector3(), Vector3 v3 = Vector3());

  Triangle (float v1[3], float v2[3], float v3[3]);

  Triangle &operator= (const Triangle &param);
};
}
