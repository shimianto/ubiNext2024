#include "stdafx.h"
#include "App/app.h"
#include "Renderer.h"
#include "..\Graphics3D\Mesh.h"
#include "..\Math\Matrix.h"

using namespace Graphics3D;

Renderer::Renderer() : 
	cube (Mesh (CUBE)), 
	fTheta (0.0f)
{
}

void Renderer::Init (float fNear, float fFar, float fFov)
{
  Mesh::InitProjectionMatrix (fNear, fFar, fFov);
}

void Renderer::Update (float deltaTime)
{
  fTheta += 0.0001f * deltaTime;
  cube.Update(deltaTime, fTheta);
}

void Renderer::Render()
{
  App::Print (450, 700, "Ubi Next 2024", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
  cube.Render();
}

