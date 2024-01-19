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

Vector3 Triangle::GetSurfaceNormal()
{
  Vector3 sNormal, line1, line2;
  line1 = vertices[1] - vertices[0];
  line2 = vertices[2] - vertices[0];

  sNormal = Vector3::CrossProduct (line1, line2);

  return sNormal;
}

Triangle &Triangle::operator= (const Triangle &param)
{
  vertices[0] = param.vertices[0];
  vertices[1] = param.vertices[1];
  vertices[2] = param.vertices[2];

  return *this;
}

Triangle Triangle::operator+ (const Vector3 &param)
{
  Triangle out;

  out.vertices[0] = this->vertices[0] + param;
  out.vertices[1] = this->vertices[1] + param;
  out.vertices[2] = this->vertices[2] + param;

  return out;
}

bool Triangle::operator> (const Triangle &param)
{
  float z1 = vertices->Magnitude() / 3.0f;
  float z2 = param.vertices->Magnitude() / 3.0f;

  return z1 > z2;
}

bool Triangle::operator>= (const Triangle &param)
{
  float z1 = vertices->Magnitude() / 3.0f;
  float z2 = param.vertices->Magnitude() / 3.0f;

  return z1 > z2 || z1==z2;
}

bool Triangle::operator< (const Triangle &param)
{
  float z1 = vertices->Magnitude() / 3.0f;
  float z2 = param.vertices->Magnitude() / 3.0f;

  return z1 < z2;
}

bool Triangle::operator<= (const Triangle &param)
{
  float z1 = vertices->Magnitude() / 3.0f;
  float z2 = param.vertices->Magnitude() / 3.0f;

  return z1 < z2 || z1 == z2;
}

