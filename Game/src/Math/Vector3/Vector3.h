#pragma once
#include <string>

class Matrix;

class Vector3
{
  public:
  float x, y, z, w;

  Vector3 (float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);

  Vector3 (float coords[3]);

  bool Vector3::operator== (const Vector3 &other) const;

  Vector3 operator* (const Matrix &matrix);

  Vector3 operator+ (const Vector3 &other) const;

  Vector3 &operator+= (const Vector3 &other);

  Vector3 operator- (const Vector3 &other) const;

  Vector3 &operator-= (const Vector3 &other);

  float operator* (const Vector3 &other) const;

  Vector3 operator* (float scalar) const;

  Vector3 operator*= (float scalar);

  Vector3 operator/ (float scalar) const;

  Vector3 operator/= (float scalar);

  float Magnitude() const;

  Vector3 Normalize() const;

  static Vector3 CrossProduct (const Vector3 &v1, const Vector3 &v2);
};

