#include "stdafx.h"
#include "Vector3Test.cpp"
#include "MatrixTest.cpp"
#include "TriangleTest.cpp"

class UnitTesting
{
  public:
  static void RunAll()
  {
	Vector3Test::Run();
	MatrixTest::Run();
	TriangleTest::Run();
  }
};