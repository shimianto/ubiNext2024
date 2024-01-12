#pragma once

#include "Graphics3D/Vector3.h"
#include "Graphics3D/Triangle.h"
#include "Graphics3D/Mesh.h"

namespace Graphics3D {
	//*******************************************************************************************
	// Display Calls.
	//*******************************************************************************************
	//-------------------------------------------------------------------------------------------
	// void DrawTriangle( Triangle t, float r = 1.0f, float g = 1.0f, float b = 1.0f );
	//-------------------------------------------------------------------------------------------
	// Draw a 2D Triangle using the vertices' coordinates from t, using color r = red, g = green, b=blue.
	//-------------------------------------------------------------------------------------------
	void DrawTriangle (Triangle t, float r = 1.0f, float g = 1.0f, float b = 1.0f);
}