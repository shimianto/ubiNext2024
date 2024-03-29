#pragma once
#include "..\Vector3\Vector3.h"
#include "../../Graphics3D/Color/Color.h"

class Triangle
{
  public:

  Color col;
  Vector3 vertices[3];

  Triangle (Vector3 v1 = Vector3(), Vector3 v2 = Vector3(), Vector3 v3 = Vector3());

  Triangle (float v1[3], float v2[3], float v3[3]);

  Vector3 GetSurfaceNormal();

  Triangle &operator= (const Triangle &param);
  Triangle operator+ (const Vector3 &param);
  bool operator> (const Triangle &param);
  bool operator>= (const Triangle &param);
  bool operator< (const Triangle &param);
  bool operator<= (const Triangle &param);
};
