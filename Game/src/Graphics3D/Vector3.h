#pragma once
#include <string>
#include "..\\Math\Matrix.h"

class Vector3
{
  public:
  float x, y, z;

  Vector3 (float x = 0.0f, float y = 0.0f, float z = 0.0f);

  Vector3 (float coords[3]);

  Vector3 operator* (const Matrix &matrix);

  Vector3 operator+ (const Vector3 &other) const;

  Vector3 &operator+= (const Vector3 &other);

  Vector3 operator- (const Vector3 &other) const;

  Vector3 &operator-= (const Vector3 &other);

  float Vector3::operator* (const Vector3 &other) const;

  Vector3 operator* (float scalar) const;

  Vector3 operator*= (float scalar);

  Vector3 operator/ (float scalar) const;

  Vector3 operator/= (float scalar);

  Vector3 Normalize() const;

  std::string ToString (int precision = 2) const;
};

