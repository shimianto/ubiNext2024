#include "stdafx.h"
#include "UIManager.h"
#include "../../UI/UI.h"
#include "../../Scene.h"

void UIManager::Init (const Scene &scene)
{
  UI menuUI;
  UIText menuText  (Vector3 (450, 700), "Menu: Ubi Next 2024", Color());
  menuUI.InsertNewText (menuText);
  RegisterUI (MENU_SCENE, menuUI);
  
  UI mainGameUI;
  UIText mainText (Vector3 (450, 700), "Main Scene", Color());
  mainGameUI.InsertNewText (mainText);
  RegisterUI (MAIN_SCENE, mainGameUI);

  UI gridUI;
  UIText gridText (Vector3 (450, 700), "Gird Test", Color());
  UIBar gridBar (Vector3 (450, 690), Vector3 (100, 5), 1);
  gridUI.InsertNewText (gridText);
  gridUI.InsertNewBar (gridBar);
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

void UIManager::RegisterUI (const SceneType &sceneType, UI &ui)
{
  uiMap_.insert (std::pair<SceneType, UI> (sceneType, ui));
}

UI &UIManager::GetActiveUI (const Scene &scene)
{
  return uiMap_[scene.GetActiveScene()];
}
	