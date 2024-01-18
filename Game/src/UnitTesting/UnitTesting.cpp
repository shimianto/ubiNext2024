#include "stdafx.h"
#include "Vector3Test.cpp"
#include "MatrixTest.cpp"

class UnitTesting
{
  public:
  static void RunAll()
  {
	Vector3Test::Run();
	MatrixTest::Run();
  }
};