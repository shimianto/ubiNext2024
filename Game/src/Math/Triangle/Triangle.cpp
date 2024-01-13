#include <App/app.h>
#include "stdafx.h"
#include "Triangle.h"
#include "..\Vector3\Vector3.h"

Triangle::Triangle (Vector3 v1, Vector3 v2, Vector3 v3) : 
	vertices{v1, v2, v3}
{}

Triangle::Triangle (float v1[3], float v2[3], float v3[3]) : 
	vertices{Vector3(v1), Vector3(v2), Vector3(v3)}
{}

Triangle &Triangle::operator= (const Triangle &param)
{
  vertices[0] = param.vertices[0];
  vertices[1] = param.vertices[1];
  vertices[2] = param.vertices[2];

  return *this;
}

Vector3 Triangle::GetSurfaceNormal()
{
  Vector3 sNormal, line1, line2;
  line1 = vertices[1] - vertices[0];
  line2 = vertices[2] - vertices[0];

  sNormal = Vector3::CrossProduct (line1, line2);

  return sNormal;
}
