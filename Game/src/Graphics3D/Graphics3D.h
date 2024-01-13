#pragma once

#include "Color\Color.h"
#include "Mesh\Mesh.h"
#include "..\Math\Triangle\Triangle.h"

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