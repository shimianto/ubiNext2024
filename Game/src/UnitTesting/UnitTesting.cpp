#include "stdafx.h"
#include "Vector3Test.cpp"
#include "MatrixTest.cpp"
#include "TriangleTest.cpp"
#include "EntityManagerTest.cpp"

class UnitTesting
{
  public:
  static void RunAll()
  {
	Vector3Test::Run();
	MatrixTest::Run();
	TriangleTest::Run();
	EntityManagerTest::Run();

	// TODO: Pooling Unit testing
	// TODO: Managers Unit testing
	// TODO: Components Unit testing
	// TODO: GameObjects Unit testing
	// TODO: Scene Unit testing
  }
};