#pragma once
#include <string>

namespace Graphics3D {
	class Vector3
	{
	public:
		float x, y, z;

		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

		Vector3(float coords[3]);

		//Vector3& operator= (const Vector3& param);

		std::string ToString(int precision = 2) const;
	};
}


