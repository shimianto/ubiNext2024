#include "stdafx.h"
#include "Graphics3D.h"
#include "App\app.h"

void Graphics3D::DrawTriangle (Triangle t, Color c)
{
  glBegin (GL_TRIANGLES);
  glColor3f (c.r, c.g, c.b); 

  for each (auto& pt in t.vertices) {

#if APP_USE_VIRTUAL_RES
	APP_VIRTUAL_TO_NATIVE_COORDS (pt.x, pt.y);
#endif

	glVertex2f (pt.x, pt.y);
  }

  glEnd();
}
