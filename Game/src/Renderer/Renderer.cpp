#include "stdafx.h"
#include "App/app.h"
#include "Renderer.h"
#include "..\Graphics3D\Mesh\Mesh.h"
#include "..\Math\Matrix\Matrix.h"

Renderer::Renderer() : 
	testMesh (Mesh ())
{
  testMesh.triangles = Mesh::LoadTrianglesFromObjectFile (".\\TestData\\VideoShip.obj");
}

void Renderer::Init ()
{}

void Renderer::Update (float deltaTime)
{
  testMesh.Update(deltaTime);
}

void Renderer::Render()
{
  App::Print (450, 700, "Ubi Next 2024", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
  testMesh.Render();
}

