#include "stdafx.h"
#include "Quad.h"

Quad::Quad (Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) : 
	vertices{v1, v2, v3, v4}
{
}

Quad::Quad (float v1[3], float v2[3], float v3[3], float v4[3]) : 
	vertices{v1, v2, v3, v4}
{
}
