#include <sstream>
#include <iomanip>

#include "stdafx.h"
#include "Vector3.h"
#include "..\Matrix\Matrix.h"

Vector3::Vector3 (float x, float y, float z) : x (x), y (y), z (z)
{
}

Vector3::Vector3 (float coords[3]) : x (coords[0]), y (coords[1]), z (coords[2])
{
}

Vector3 Vector3::operator* (const Matrix &matrix)
{
  Vector3 out;

  out.x = x * matrix.m[0][0] + y * matrix.m[1][0] + z * matrix.m[2][0] + matrix.m[3][0];
  out.y = x * matrix.m[0][1] + y * matrix.m[1][1] + z * matrix.m[2][1] + matrix.m[3][1];
  out.z = x * matrix.m[0][2] + y * matrix.m[1][2] + z * matrix.m[2][2] + matrix.m[3][2];
  float w = x * matrix.m[0][3] + y * matrix.m[1][3] + z * matrix.m[2][3] + matrix.m[3][3];

  if (w != 0.0f) {
	out.x /= w;
	out.y /= w;
	out.z /= w;
  }

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

Vector3 Vector3::Normalize() const
{
  Vector3 normal;
  float lenght = x * x + y * y + z * z;
  normal = *this / sqrtf (lenght);
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
