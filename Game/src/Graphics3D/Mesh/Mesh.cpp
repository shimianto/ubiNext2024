#include "stdafx.h"
#include "Mesh.h"

#include <string>
#include <fstream>
#include <strstream>
#include <algorithm>
#include <App/app.h>
//---------------------------------------------------------------------------------
#include "..\../Renderer/Renderer.h"
#include "App/main.h"
#include "../Graphics3D.h"

using namespace std;

Mesh::Mesh ()
{
  
}
void Mesh::Update (float deltaTime, float fTheta)
{
  RotateMesh (fTheta);
  UpdateVisibleTriangles();
  SortVisibleTriangles();
}
void Mesh::Render()
{
  DrawMesh();
}
void Mesh::UpdateVisibleTriangles()
{
  Vector3 vCam;
  visibleTriangles.clear();
  
  for (auto tri : triangles) {
	Triangle triProjected;
	Triangle triTranslated, triRotatedZ, triRotatedZX;

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

	if (normal * (triTranslated.vertices[0] - vCam) >= 0.0f) 
	{
	  continue;
	}

	// Project triangles from 3D --> 2D
	triProjected.vertices[0] = triTranslated.vertices[0] * Matrix::PROJ_MAT;
	triProjected.vertices[1] = triTranslated.vertices[1] * Matrix::PROJ_MAT;
	triProjected.vertices[2] = triTranslated.vertices[2] * Matrix::PROJ_MAT;

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

	visibleTriangles.push_back (triProjected);
  }
}

void Mesh::SortVisibleTriangles()
{
  sort (visibleTriangles.begin(), visibleTriangles.end(), [] (Triangle &t1, Triangle &t2) {
	
	float z1 = (t1.vertices[0].z + t1.vertices[1].z + t1.vertices[2].z) / 3.0f;
	float z2 = (t2.vertices[0].z + t2.vertices[1].z + t2.vertices[2].z) / 3.0f;
	return z1 > z2;	
  });
}
void Mesh::DrawMesh()
{
  for (auto tri : visibleTriangles) {
	App::DrawLine (tri.vertices[0].x, tri.vertices[0].y, tri.vertices[1].x, tri.vertices[1].y, 0, 0, 0);
	App::DrawLine (tri.vertices[1].x, tri.vertices[1].y, tri.vertices[2].x, tri.vertices[2].y, 0, 0, 0);
	App::DrawLine (tri.vertices[2].x, tri.vertices[2].y, tri.vertices[0].x, tri.vertices[0].y, 0, 0, 0);

	Graphics3D::DrawTriangle (tri, Color());
  }
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
  matRotZ = Matrix::Matrix_MakeRotationZ(fTheta);

  // Rotation X
  matRotX = Matrix::Matrix_MakeRotationX(fTheta);
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