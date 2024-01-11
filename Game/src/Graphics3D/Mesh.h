#pragma once
#include "Triangle.h"
#include <vector>

namespace Graphics3D {
	enum MeshTypes
	{
		Cube
	};

	class Mesh
	{
	public:
		std::vector<Triangle> triangles;
	};
}

