#include "stdafx.h"
#include "../Math/Matrix/Matrix.h"
#include "../Math/Vector3/Vector3.h"

class MatrixTest
{
  public:
  static void Run()
  {
	Matrix m1;
	Matrix m2;
	for (int row = 0; row < 4; row++) {
	  for (int col = 0; col < 4; col++) {
		m1 (row, col) = 10;
		m2 (row, col) = 20;
	  }
	}
	Vector3 v1 = Vector3 (1, 2, 3);

	TestConstructor();
	TestMultiplyMatrix (m1, m2);
	TestIdentity();
	TestTranslate (v1);
  }

  private:

  static void TestConstructor()
  {
	Matrix m = Matrix();

	for (int row = 0; row < 4; row++) {
	  for (int col = 0; col < 4; col++) {
		assert (m (row, col) == 0);
	  }
	}
  }

  static void TestMultiplyMatrix (Matrix &a, Matrix &b)
  {
	Matrix m = a * b;

	for (int row = 0; row < 4; row++) {
	  for (int col = 0; col < 4; col++) {
		assert (m (row, col) == 800);
	  }
	}
  }

  static void TestIdentity()
  {
	Matrix m = Matrix::Identity ();

	assert (m (0, 0) == 1);
	assert (m (0, 1) == 0);
	assert (m (0, 2) == 0);
	assert (m (0, 3) == 0);
	assert (m (1, 0) == 0);
	assert (m (1, 1) == 1);
	assert (m (1, 2) == 0);
	assert (m (1, 3) == 0);
	assert (m (2, 0) == 0);
	assert (m (2, 1) == 0);
	assert (m (2, 2) == 1);
	assert (m (2, 3) == 0);
	assert (m (3, 0) == 0);
	assert (m (3, 1) == 0);
	assert (m (3, 2) == 0);
	assert (m (3, 3) == 1);
  }

  static void TestTranslate (Vector3 &v)
  {
	Matrix m = Matrix::Translate (v);

	assert (m (0, 0) == 1);
	assert (m (0, 1) == 0);
	assert (m (0, 2) == 0);
	assert (m (0, 3) == 0);
	assert (m (1, 0) == 0);
	assert (m (1, 1) == 1);
	assert (m (1, 2) == 0);
	assert (m (1, 3) == 0);
	assert (m (2, 0) == 0);
	assert (m (2, 1) == 0);
	assert (m (2, 2) == 1);
	assert (m (2, 3) == 0);
	assert (m (3, 0) == 1);
	assert (m (3, 1) == 2);
	assert (m (3, 2) == 3);
	assert (m (3, 3) == 1);
  }
};