#include <sstream>
#include <iomanip>

#include "stdafx.h"
#include "Vector3.h"
#include "..\Matrix\Matrix.h"

Vector3::Vector3 (float x, float y, float z, float w) : x (x), y (y), z (z), w(w)
{
}

Vector3::Vector3 (float coords[3]) : x (coords[0]), y (coords[1]), z (coords[2])
{
}

Vector3 Vector3::operator* (const Matrix &m)
{
  Vector3 out;
  out.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + w * m.m[3][0];
  out.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + w * m.m[3][1];
  out.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + w * m.m[3][2];
  out.w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + w * m.m[3][3];

  return out;
}

 Vector3 Vector3::operator+ (const Vector3 &other) const
{
  return Vector3 (x + other.x, y + other.y, z + other.z);
}

Vector3 &Vector3::operator+= (const Vector3 &other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Vector3 Vector3::operator- (const Vector3 &other) const
{
  return Vector3 (x - other.x, y - other.y, z - other.z);
}

Vector3 &Vector3::operator-= (const Vector3 &other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

float Vector3::operator* (const Vector3 &other) const
{
  return 
	  x * other.x + 
	  y * other.y + 
	  z * other.z;
}

Vector3 Vector3::operator* (float scalar) const
{
  return Vector3 (x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator*= (float scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

Vector3 Vector3::operator/ (float scalar) const
{
  return Vector3 (x / scalar, y / scalar, z / scalar);
}

Vector3 Vector3::operator/= (float scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

float Vector3::Magnitude() const
{
  return x * x + y * y + z * z;
}

Vector3 Vector3::Normalize() const
{
  Vector3 normal;
  normal = *this / sqrtf (this->Magnitude());
  return normal;
}

std::string Vector3::ToString (int precision) const
{
  std::ostringstream sX, sY, sZ;

  sX << std::fixed;
  sY << std::fixed;
  sZ << std::fixed;

  sX << std::setprecision (precision);
  sY << std::setprecision (precision);
  sZ << std::setprecision (precision);

  sX << x;
  sY << y;
  sZ << z;

  return "(" + sX.str() + ", " + sY.str() + ", " + sZ.str() + ")";
}

Vector3 Vector3::CrossProduct (const Vector3 &v1, const Vector3 &v2)
{
  Vector3 out;

  out.x = v1.y * v2.z - v1.z * v2.y;
  out.y = v1.z * v2.x - v1.x * v2.z;
  out.z = v1.x * v2.y - v1.y * v2.x;

  return out;
}
