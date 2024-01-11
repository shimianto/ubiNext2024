#include <sstream>
#include <iomanip>

#include "stdafx.h"
#include "Vector3.h"

namespace Graphics3D {

	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3::Vector3(float coords[3]) : x(coords[0]), y(coords[1]), z(coords[2])
	{
	}

	//Vector3& Vector3::operator=(const Vector3& param)
	//{
	//	x = param.x;
	//	y = param.y;
	//	z = param.z;

	//	return *this;
	//}

	std::string Vector3::ToString(int precision) const {
		std::ostringstream sX, sY, sZ;

		sX << std::fixed;
		sY << std::fixed;
		sZ << std::fixed;

		sX << std::setprecision(precision);
		sY << std::setprecision(precision);
		sZ << std::setprecision(precision);

		sX << x;
		sY << y;
		sZ << z;

		return "(" + sX.str() + ", " + sY.str() + ", " + sZ.str() + ")";
	}
}
