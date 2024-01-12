#include "stdafx.h"
#include "App/app.h"
#include "Renderer.h"
#include "..\Graphics3D\Mesh.h"
#include "..\Math\Matrix.h"

Renderer::Renderer() : 
	cube (Mesh ()), 
	fTheta (0.0f)
{
  cube.triangles = Mesh::LoadTrianglesFromObjectFile (".\\TestData\\VideoShip.obj");
}

void Renderer::Init ()
{}

void Renderer::Update (float deltaTime)
{
  fTheta += 0.0005f * deltaTime;
  cube.Update(deltaTime, fTheta);
}

void Renderer::Render()
{
  App::Print (450, 700, "Ubi Next 2024", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
  cube.Render();
}

