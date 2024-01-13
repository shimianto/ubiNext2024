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
#include "../Camera/Camera.h"

using namespace std;

Mesh::Mesh ()
{
  
}
void Mesh::Update (float deltaTime)
{
  UpdateVisibleTriangles (deltaTime);
  SortVisibleTriangles();
}
void Mesh::Render()
{
  DrawMesh();
}

void Mesh::UpdateVisibleTriangles (float deltaTime)
{
  fTheta += 0.0005 * deltaTime;
  Matrix matRotZ = Matrix::MakeRotationMatrixZ (fTheta);
  Matrix matRotX = Matrix::MakeRotationMatrixX (fTheta);

  Matrix matTrans;
  Vector3 vecTrans(0.0f, 0.0f, 8.0f);
  matTrans = Matrix::Translate(vecTrans);

  Matrix matWorld;
  matWorld = Matrix::Identity(); // Form World Matrix
  matWorld = matRotZ * matRotX; // Transform by rotation
  matWorld = matWorld * matTrans; // Transform by translation

  Camera::mainCamera.UpdateViewMatrices();
  
  visibleTriangles.clear();

  for (auto tri : triangles) {
	Triangle triProjected, triTransformed, triViewed;

	// World Matrix Transform
	triTransformed.vertices[0] = tri.vertices[0] * matWorld;
	triTransformed.vertices[1] = tri.vertices[1] * matWorld;
	triTransformed.vertices[2] = tri.vertices[2] * matWorld;

	// Use Cross-Product to get surface normal
	Vector3 normal = triTransformed.GetSurfaceNormal().Normalize();

	if (normal * (triTransformed.vertices[0] - Camera::mainCamera.pos) >= 0.0f) {
	  continue;
	}

	// Convert World Space --> View Space
	triViewed.vertices[0] = triTransformed.vertices[0] * Camera::mainCamera.GetViewMatrix();
	triViewed.vertices[1] = triTransformed.vertices[1] * Camera::mainCamera.GetViewMatrix();
	triViewed.vertices[2] = triTransformed.vertices[2] * Camera::mainCamera.GetViewMatrix();

	// Project triangles from 3D --> 2D
	triProjected.vertices[0] = triViewed.vertices[0] * Matrix::projMat;
	triProjected.vertices[1] = triViewed.vertices[1] * Matrix::projMat;
	triProjected.vertices[2] = triViewed.vertices[2] * Matrix::projMat;

	triProjected.vertices[0] = triProjected.vertices[0] / triProjected.vertices[0].w;
	triProjected.vertices[1] = triProjected.vertices[1] / triProjected.vertices[1].w;
	triProjected.vertices[2] = triProjected.vertices[2] / triProjected.vertices[2].w;

	// Scale into view
	// Offset verts into visible normalised space
	Vector3 vOffsetView = {1, 1, 0};
	triProjected.vertices[0] = triProjected.vertices[0] + vOffsetView;
	triProjected.vertices[1] = triProjected.vertices[1] + vOffsetView;
	triProjected.vertices[2] = triProjected.vertices[2] + vOffsetView;
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