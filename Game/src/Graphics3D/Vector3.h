#pragma once
#include <string>
namespace Graphics3D {
	class Vector3
	{
	public:
		float X, Y, Z;

		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

		std::string ToString(int precision = 2) const;
	};
}


