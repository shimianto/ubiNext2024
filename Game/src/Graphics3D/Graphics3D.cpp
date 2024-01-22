#include "Graphics3D.h"

#include "App/app.h"
#include "../Scene/UI/UI.h"
#include "../Math/Triangle/Triangle.h"
#include "../Math/Quad/Quad.h"
#include "Color/Color.h"

void Graphics3D::DrawTriangle (Triangle t, Color c)
{
  glBegin (GL_TRIANGLES);
  glColor3f (c.r, c.g, c.b); 

  for (auto& pt : t.vertices) {

#if APP_USE_VIRTUAL_RES
	APP_VIRTUAL_TO_NATIVE_COORDS (pt.x, pt.y);
#endif

	glVertex2f (pt.x, pt.y);
  }

  glEnd();
}

void Graphics3D::DrawQuad (Quad q, Color c)
{
  glBegin (GL_QUADS);
  glColor3f (c.r, c.g, c.b);

  for (auto &pt : q.vertices) {

#if APP_USE_VIRTUAL_RES
	APP_VIRTUAL_TO_NATIVE_COORDS (pt.x, pt.y);
#endif

	glVertex2f (pt.x, pt.y);
  }

  glEnd();
}

void Graphics3D::DrawBar (const UIBar &bar)
{
  App::DrawLine (
    bar.coords.vertices[0].x, bar.coords.vertices[0].y, bar.coords.vertices[1].x, bar.coords.vertices[1].y, bar.color.r, bar.color.g, bar.color.b);
  App::DrawLine (
    bar.coords.vertices[1].x, bar.coords.vertices[1].y, bar.coords.vertices[2].x, bar.coords.vertices[2].y, bar.color.r, bar.color.g, bar.color.b);
  App::DrawLine (
    bar.coords.vertices[2].x, bar.coords.vertices[2].y, bar.coords.vertices[3].x, bar.coords.vertices[3].y, bar.color.r, bar.color.g, bar.color.b);
  App::DrawLine (
    bar.coords.vertices[3].x, bar.coords.vertices[3].y, bar.coords.vertices[0].x, bar.coords.vertices[0].y, bar.color.r, bar.color.g, bar.color.b);

  Quad filledBar = bar.coords;
  filledBar.vertices[2].x = ((filledBar.vertices[2].x - filledBar.vertices[1].x) * bar.fill) + filledBar.vertices[1].x;
  filledBar.vertices[3].x = ((filledBar.vertices[3].x - filledBar.vertices[0].x) * bar.fill) + filledBar.vertices[0].x;

  Graphics3D::DrawQuad (filledBar, bar.color);
}
