#pragma once

#include "stdafx.h"
#include "../Math/Vector3/Vector3.h"
#include "../Math/Matrix/Matrix.h"

class Vector3Test
{
  public:
  static void Run()
  {
	Vector3 v1 = Vector3 (1.0f, 2.0f, 3.0f);
	Vector3 v2 = Vector3 (4.0f, 5.0f, 6.0f);
	Matrix m1;

	for (int i = 0; i < 4; i++) {
	  for (int j = 0;  j< 4; j++) {
		m1.m[i][j] = 2;
	  }
	}

	float scalar = 2.0f;

	TestConstructor();
	TestConstructor2();

	TestMatrixMultiply (v1, m1);

	TestAdd (v1, v2);
	TestCompoundAdd (v1, v2);
	TestSubtract (v1, v2);
	TestCompoundSubtract (v1, v2);

	TestMultiplyVector (v1, v2);

	TestMultiplyScalar (v1, scalar);
	TestCompoundMultiply (v1, scalar);
	TestDivide (v1, scalar);
	TestCompoundDivide (v1, scalar);

	TestMagnitude (v1);
	TestNormalize (v1);
	TestCrossProduct (v1, v2);
  }

  private:
  static void TestConstructor()
  {
	Vector3 vf;

	assert (vf.x == 0);
	assert (vf.y == 0);
	assert (vf.z == 0);
	assert (vf.w == 1);
  }

  static void TestConstructor2()
  {
	Vector3 vf({1.0f, 2.0f, 3.0f});

	assert (vf.x == 1);
	assert (vf.y == 2);
	assert (vf.z == 3);
	assert (vf.w == 1);
  }

  static void TestMatrixMultiply(Vector3 &v1, Matrix &m1)
  {
	Vector3 vf = v1 * m1;

	assert (vf.x == 14);
	assert (vf.y == 14);
	assert (vf.z == 14);
	assert (vf.w == 14);
  }

  static void TestAdd (Vector3 &v1, Vector3 &v2)
  {
	Vector3 vf = v1 + v2;

	assert (vf == Vector3 (5.0f, 7.0f, 9.0f));
  }

  static void TestCompoundAdd (Vector3 &v1, Vector3 &v2)
  {
	Vector3 vf = v1;
	vf += v2;

	assert (vf == Vector3 (5.0f, 7.0f, 9.0f));
  }

  static void TestSubtract (Vector3 &v1, Vector3 &v2)
  {
	Vector3 vf = v1 - v2;

	assert (vf == Vector3 (-3.0f, -3.0f, -3.0f));
  }

  static void TestCompoundSubtract (Vector3 &v1, Vector3 &v2)
  {
	Vector3 vf = v1;
	vf -= v2;

	assert (vf == Vector3 (-3.0f, -3.0f, -3.0f));
  }

  static void TestMultiplyVector (Vector3 &v1, Vector3 &v2)
  {
	float result = v1 * v2;

	assert (result == 32);
  }

  static void TestMultiplyScalar (Vector3 &v, float &scalar)
  {
	Vector3 vf = v * scalar;

	assert (vf == Vector3 (2.0f, 4.0f, 6.0f));
  }

  static void TestCompoundMultiply (Vector3 &v, float &scalar)
  {
	Vector3 vf = v;
	vf *= scalar;

	assert (vf == Vector3 (2.0f, 4.0f, 6.0f));
  }

  static void TestDivide (Vector3 &v, float &scalar)
  {
	Vector3 vf = v / scalar;

	assert (vf == Vector3 (0.5f, 1.0f, 1.5f));
  }

  static void TestCompoundDivide (Vector3 &v, float &n)
  {
	Vector3 vf = v;
	vf /= n;

	assert (vf == Vector3 (0.5f, 1.0f, 1.5f));
  }

  static void TestMagnitude (Vector3 &v)
  {
	assert (v.Magnitude() == 14);
  }

  static void TestNormalize (Vector3 &v)
  {
	Vector3 vf = v.Normalize();

	assert (vf == Vector3 ((float)(v.x / sqrtf (14)), (float)(v.y / sqrtf (14)), (float)(v.z / sqrtf (14))));
  }

  static void TestCrossProduct (Vector3 &v1, Vector3 &v2)
  {
	Vector3 vf = Vector3::CrossProduct (v1, v2);

	assert (vf == Vector3 (-3.0f, 6.0f, -3.0f));
  }
};