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
#include "Scene/Managers/UIManager/UIManager.h"

Scene mainScene;
UIManager uiManager;

void Init()
{
  mainScene.SetScene (PARTICLES_SCENE);
  mainScene.Init (uiManager);
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