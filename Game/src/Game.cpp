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
#include "Scene/Scene.h"

Scene mainScene;

void Init()
{
  mainScene.SetScreen (GRID_TEST);
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