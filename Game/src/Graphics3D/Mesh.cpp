#include "stdafx.h"
#include "Mesh.h"

#include <string>
#include <fstream>
#include <strstream>
#include <algorithm>
#include <App/app.h>
//---------------------------------------------------------------------------------
#include "../Renderer/Renderer.h"
#include "App/main.h"
#include "../Graphics3D.h"

using namespace std;

Matrix Mesh::projectionMatrix = Matrix();
float Mesh::fNear = {0}, Mesh::fFar = {0}, Mesh::fFov = {0};

Mesh::Mesh (MeshTypes type) : matRotZ (Matrix()), matRotX (Matrix())
{
  
}
void Mesh::Update (float deltaTime, float fTheta)
{
  RotateMesh (fTheta);
}
void Mesh::Render()
{
  Vector3 vCam;
  // Draw Triangles
  for (auto tri : triangles) {
	Triangle triProjected, triTranslated, triRotatedZX;
	Triangle triRotatedZ;

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
	triTranslated.vertices[0].z = triRotatedZX.vertices[0].z + 8.0f;
	triTranslated.vertices[1].z = triRotatedZX.vertices[1].z + 8.0f;
	triTranslated.vertices[2].z = triRotatedZX.vertices[2].z + 8.0f;

	// Use Cross-Product to get surface normal
	Vector3 normal = triTranslated.GetSurfaceNormal().Normalize();

	if (normal * (triTranslated.vertices[0] - vCam) >= 0.0f) {
	  continue;
	}

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
	App::DrawLine (triProjected.vertices[0].x, triProjected.vertices[0].y, triProjected.vertices[1].x, triProjected.vertices[1].y, 0, 0, 0);
	App::DrawLine (triProjected.vertices[1].x, triProjected.vertices[1].y, triProjected.vertices[2].x, triProjected.vertices[2].y, 0, 0, 0);
	App::DrawLine (triProjected.vertices[2].x, triProjected.vertices[2].y, triProjected.vertices[0].x, triProjected.vertices[0].y, 0, 0, 0);

	Graphics3D::DrawTriangle (triProjected, r, g, b);
  }
}
void Mesh::DrawMesh()
{
}
//void Mesh::SetCubeMesh()
//{
//  triangles = {
//    // SOUTH
//    Triangle ({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}),
//    Triangle ({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
//
//    // EAST
//    Triangle ({1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}),
//    Triangle ({1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}),
//
//    // NORTH
//    Triangle ({1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}),
//    Triangle ({1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}),
//
//    // WEST
//    Triangle ({0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}),
//    Triangle ({0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}),
//
//    // TOP
//    Triangle ({0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}),
//    Triangle ({0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}),
//
//    // BOTTOM
//    Triangle ({1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}),
//    Triangle ({1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
//  };
//}
void Mesh::RotateMesh (float fTheta)
{
  // Set up rotation matrices

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
void Mesh::InitProjectionMatrix (float fNear, float fFar, float fFov)
{
  Mesh::fNear = fNear;
  Mesh::fFar = fFar;
  Mesh::fFov = fFov;

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

vector<Triangle> Mesh::LoadTrianglesFromObjectFile (string fileName)
{
  vector<Triangle> trianglesList;

  ifstream f (fileName);
  if (!f.is_open())
	return trianglesList;

  // Local cache of verticess
  vector<Vector3> vertices;

  while (!f.eof()) {
	char line[128];
	f.getline (line, 128);

	strstream s;
	s << line;

	char junk;

	if (line[0] == 'v') {
	  Vector3 v;
	  s >> junk >> v.x >> v.y >> v.z;
	  vertices.push_back (v);
	}

	if (line[0] == 'f') {
	  int f[3];
	  s >> junk >> f[0] >> f[1] >> f[2];
	  trianglesList.push_back ({vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1]});
	}
  }

  return trianglesList;
}