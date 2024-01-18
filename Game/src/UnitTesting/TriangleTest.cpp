#include "stdafx.h"
#include "../Math/Triangle/Triangle.h"
#include "../Math/Vector3/Vector3.h"

class TriangleTest
{
  public:
	  static void Run()
	  {
		Triangle t1(Vector3(1,2,3), Vector3(4,5,6), Vector3(7,8,9));
	    Vector3 v1 (1, 2, 3), v2(4,5,6), v3(7,8,9);

		TestConstructor(v1, v2, v3);
	    TestVectorAdd(t1, v1);
	    TestGetSurfaceNormal (t1);
	  }

  private:

	  static void TestConstructor(Vector3 &v1, Vector3 &v2, Vector3 &v3)
      {
	    Triangle tf (v1, v2, v3);

		assert (tf.vertices[0] == Vector3 (1, 2, 3));
	    assert (tf.vertices[1] == Vector3 (4, 5, 6));
	    assert (tf.vertices[2] == Vector3 (7, 8, 9));
      }

	  static void TestVectorAdd (Triangle &t1, Vector3 &v1)
      {
	    Triangle tf = t1 + v1;

		assert (tf.vertices[0] == Vector3(2,4,6));
	    assert (tf.vertices[1] == Vector3 (5, 7, 9));
	    assert (tf.vertices[2] == Vector3 (8, 10, 12));
      }

	  static void TestGetSurfaceNormal (Triangle &t1)
      {
	    Vector3 sNormal = t1.GetSurfaceNormal();

		assert (sNormal.x == 0);
	    assert (sNormal.y == 0);
	    assert (sNormal.z == 0);
	  }
};