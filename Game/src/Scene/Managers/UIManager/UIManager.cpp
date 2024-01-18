#include "stdafx.h"
#include "UIManager.h"
#include "../../Scene.h"

void UIManager::Init (const Scene &scene)
{
  UI menuUI;
  menuUI.InsertNewText (Vector3 (450, 700), "Menu: Ubi Next 2024", Color());
  RegisterUI (MENU_SCENE, menuUI);
  
  UI mainGameUI;
  mainGameUI.InsertNewText (Vector3 (450, 700), "Main Scene", Color());
  RegisterUI (MAIN_SCENE, mainGameUI);

  UI gridUI;
  gridUI.InsertNewText (Vector3 (450, 700), "Gird Test", Color());
  gridUI.InsertNewBar (Vector3 (450, 690), Vector3 (100, 5), 1);
  RegisterUI (GRID_TEST, gridUI);

  uiMap_[scene.GetActiveScene()].Init();
}

void UIManager::Update (const Scene &scene)
{
  uiMap_[scene.GetActiveScene()].Update();
}

void UIManager::Render (const Scene &scene)
{
  uiMap_[scene.GetActiveScene()].Render();
}

void UIManager::RegisterUI (const SceneType &screen, UI &ui)
{
  uiMap_.insert (std::pair<SceneType, UI> (screen, ui));
}

UI UIManager::GetActiveUI (const Scene &scene)
{
  return uiMap_[scene.GetActiveScene()];
}
	