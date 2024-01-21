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
#include "UnitTesting/UnitTesting.cpp"

Scene mainScene;
UIManager uiManager;

void Init()
{
  UnitTesting::RunAll();
  mainScene.Init (uiManager, MENU_SCENE);
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