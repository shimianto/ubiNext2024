#include "stdafx.h"
#include "App/app.h"
#include "Renderer.h"
#include "..\Graphics3D\Mesh.h"
#include "..\Math\Matrix.h"

using namespace Graphics3D;

Renderer::Renderer() : 
	cube (Mesh (CUBE)), 
	projectionMatrix(Matrix()), 
	matRotZ (Matrix()), 
	matRotX (Matrix()), 
	fTheta (0.0f)
{
}

void Renderer::Init (float fNear, float fFar, float fFov)
{
  // Projection Matrix
  float fAspectRatio = (float)APP_INIT_WINDOW_HEIGHT / (float)APP_INIT_WINDOW_WIDTH;
  float fFovRad = 1.0f / tanf (fFov * 0.5f / 180.0f * 3.14159f);

  projectionMatrix.m[0][0] = fAspectRatio * fFovRad;
  projectionMatrix.m[1][1] = fFovRad;
  projectionMatrix.m[2][2] = fFar / (fFar - fNear);
  projectionMatrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
  projectionMatrix.m[2][3] = 1.0f;
  projectionMatrix.m[3][3] = 0.0f;
}

void Renderer::Update (float deltaTime)
{
  // Set up rotation matrices
  fTheta += 0.0001f * deltaTime;

  // Rotation Z
  matRotZ.m[0][0] = cosf (fTheta);
  matRotZ.m[0][1] = sinf (fTheta);
  matRotZ.m[1][0] = -sinf (fTheta);
  matRotZ.m[1][1] = cosf (fTheta);
  matRotZ.m[2][2] = 1;
  matRotZ.m[3][3] = 1;

  // Rotation X
  matRotX.m[0][0] = 1;
  matRotX.m[1][1] = cosf (fTheta * 0.5f);
  matRotX.m[1][2] = sinf (fTheta * 0.5f);
  matRotX.m[2][1] = -sinf (fTheta * 0.5f);
  matRotX.m[2][2] = cosf (fTheta * 0.5f);
  matRotX.m[3][3] = 1;
}

void Renderer::Render()
{
  App::Print (450, 700, "Ubi Next 2024", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);

  // Draw Triangles
  for (auto tri : cube.triangles) {
	Triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

	// Rotate in Z-Axis
	triRotatedZ.vertices[0] = tri.vertices[0] * matRotZ;
	triRotatedZ.vertices[1] = tri.vertices[1] * matRotZ;
	triRotatedZ.vertices[2] = tri.vertices[2] * matRotZ;


	// Rotate in X-Axis
	triRotatedZX.vertices[0] = triRotatedZ.vertices[0] * matRotX;
	triRotatedZX.vertices[1] = triRotatedZ.vertices[1] * matRotX;
	triRotatedZX.vertices[2] = triRotatedZ.vertices[2] * matRotX;


	// Offset into the screen
	triTranslated = triRotatedZX;
	triTranslated.vertices[0].z = triRotatedZX.vertices[0].z + 3.0f;
	triTranslated.vertices[1].z = triRotatedZX.vertices[1].z + 3.0f;
	triTranslated.vertices[2].z = triRotatedZX.vertices[2].z + 3.0f;

	// Project triangles from 3D --> 2D
	triProjected.vertices[0] = triTranslated.vertices[0] * projectionMatrix;
	triProjected.vertices[1] = triTranslated.vertices[1] * projectionMatrix;
	triProjected.vertices[2] = triTranslated.vertices[2] * projectionMatrix;


	// Scale into view
	triProjected.vertices[0].x += 1.0f;
	triProjected.vertices[0].y += 1.0f;
	triProjected.vertices[1].x += 1.0f;
	triProjected.vertices[1].y += 1.0f;
	triProjected.vertices[2].x += 1.0f;
	triProjected.vertices[2].y += 1.0f;
	triProjected.vertices[0].x *= 0.5f * (float)APP_INIT_WINDOW_WIDTH;
	triProjected.vertices[0].y *= 0.5f * (float)APP_INIT_WINDOW_HEIGHT;
	triProjected.vertices[1].x *= 0.5f * (float)APP_INIT_WINDOW_WIDTH;
	triProjected.vertices[1].y *= 0.5f * (float)APP_INIT_WINDOW_HEIGHT;
	triProjected.vertices[2].x *= 0.5f * (float)APP_INIT_WINDOW_WIDTH;
	triProjected.vertices[2].y *= 0.5f * (float)APP_INIT_WINDOW_HEIGHT;

	// Rasterize triangle
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	App::DrawLine (triProjected.vertices[0].x, triProjected.vertices[0].y, triProjected.vertices[1].x, triProjected.vertices[1].y, r, g, b);
	App::DrawLine (triProjected.vertices[1].x, triProjected.vertices[1].y, triProjected.vertices[2].x, triProjected.vertices[2].y, r, g, b);
	App::DrawLine (triProjected.vertices[2].x, triProjected.vertices[2].y, triProjected.vertices[0].x, triProjected.vertices[0].y, r, g, b);
  }
}
