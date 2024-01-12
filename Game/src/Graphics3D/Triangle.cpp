#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle (Vector3 v1, Vector3 v2, Vector3 v3)
{
  vertices[0] = v1;
  vertices[1] = v2;
  vertices[2] = v3;
}

Triangle::Triangle (float v1[3], float v2[3], float v3[3])
{
  vertices[0] = Vector3 (v1);
  vertices[1] = Vector3 (v2);
  vertices[2] = Vector3 (v3);
}

Triangle &Triangle::operator= (const Triangle &param)
{
  vertices[0] = param.vertices[0];
  vertices[1] = param.vertices[1];
  vertices[2] = param.vertices[2];

  return *this;
}

Vector3 Triangle::GetSurfaceNormal()
{
  Vector3 normal, line1, line2;
  line1 = vertices[1] - vertices[0];
  line2 = vertices[2] - vertices[0];

  normal.x = line1.y * line2.z - line1.z * line2.y;
  normal.y = line1.z * line2.x - line1.x * line2.z;
  normal.z = line1.x * line2.y - line1.y * line2.x;

  return normal;
}
