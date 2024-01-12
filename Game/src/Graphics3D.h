#pragma once

#include "Graphics3D/Vector3.h"
#include "Graphics3D/Triangle.h"
#include "Graphics3D/Mesh.h"

namespace Graphics3D {
	//*******************************************************************************************
	// Display Calls.
	//*******************************************************************************************
	//-------------------------------------------------------------------------------------------
	// void DrawTriangle( Triangle t, Color c );
	//-------------------------------------------------------------------------------------------
	// Draw a 2D Triangle using the vertices' coordinates from t, using Color c.
	//-------------------------------------------------------------------------------------------
	void DrawTriangle (Triangle t, Color c);
}