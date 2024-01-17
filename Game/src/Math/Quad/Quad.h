#pragma once
#include "../Vector3/Vector3.h"
class Quad
{
  public:
  Vector3 vertices[4];

  Quad (Vector3 v1 = Vector3(), Vector3 v2 = Vector3(), Vector3 v3 = Vector3(), Vector3 v4 = Vector3());
  Quad (float v1[3], float v2[3], float v3[3], float v4[3]);
};
