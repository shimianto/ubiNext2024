//------------------------------------------------------------------------
// Game.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>
#include <math.h>
#include <list>

//------------------------------------------------------------------------
#include "App\app.h"
#include "Math\Matrix\Matrix.h"

#include ".\\Graphics3D\Graphics3D.h"
#include "Renderer/Renderer.h"
#include "InputHandler/InputHandler.h"
#include "Graphics3D/Mesh/Mesh.h"
#include "Math/Triangle/Triangle.h"
#include "Graphics3D/Camera/Camera.h"
#include "Managers/EntityManager/EntityManager.h"


EntityManager entityManager;
Renderer renderer;
InputHandler handler;
Camera playerCam;


void Init()
{
  Mesh testMesh = Mesh(entityManager);
  testMesh.LoadTrianglesFromObjectFile (".\\TestData\\mountains.obj");
  std::list<Mesh> meshesList;
  meshesList.push_back (testMesh);

  handler.Init();
  renderer.Init (meshesList);
}

void Update (float deltaTime)
{
  handler.HandleInput (deltaTime);
  renderer.Update (deltaTime);
}

void Render()
{
  renderer.Render();
}

void Shutdown()
{
}