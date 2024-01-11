#include <sstream>
#include <iomanip>

#include "stdafx.h"
#include "Vector3.h"

namespace Graphics3D {

	Vector3::Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	std::string Vector3::ToString(int precision) const {
		std::ostringstream sX, sY, sZ;

		sX << std::fixed;
		sY << std::fixed;
		sZ << std::fixed;

		sX << std::setprecision(precision);
		sY << std::setprecision(precision);
		sZ << std::setprecision(precision);

		sX << X;
		sY << Y;
		sZ << Z;

		return "(" + sX.str() + ", " + sY.str() + ", " + sZ.str() + ")";
	}
}
