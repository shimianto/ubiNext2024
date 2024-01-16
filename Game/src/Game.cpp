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
#include "Scene/Scene.h"

Scene mainScene;

void Init()
{
  mainScene.SetScreen (MENU_SCREEN);
  mainScene.Init ();
}

void Update (float deltaTime)
{
  mainScene.Update (deltaTime);
}

void Render()
{
  mainScene.Render();
}

void Shutdown()
{
  mainScene.Shutdown();
}