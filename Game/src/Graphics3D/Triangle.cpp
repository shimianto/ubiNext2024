#include "stdafx.h"
#include "Triangle.h"
#include <App/app.h>
#include "../Graphics3D.h"
#include "Color/Color.h"

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

  sNormal.x = line1.y * line2.z - line1.z * line2.y;
  sNormal.y = line1.z * line2.x - line1.x * line2.z;
  sNormal.z = line1.x * line2.y - line1.y * line2.x;

  return sNormal;
}

void Triangle::Render (Color col)
{
  App::DrawLine (vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, 0, 0, 0);
  App::DrawLine (vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y, 0, 0, 0);
  App::DrawLine (vertices[2].x, vertices[2].y, vertices[0].x, vertices[0].y, 0, 0, 0);

  Graphics3D::DrawTriangle (*this, col);
}
