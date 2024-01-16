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
  RegisterUI (GRID_TEST, gridUI);

  m_uiMap[scene.GetSceneScreen()].Init();
}

void UIManager::Update (const Scene &scene)
{
  m_uiMap[scene.GetSceneScreen()].Update();
}

void UIManager::Render (const Scene &scene)
{
  m_uiMap[scene.GetSceneScreen()].Render();
}

void UIManager::RegisterUI (const SceneType &screen, UI &ui)
{
  m_uiMap.insert (std::pair<SceneType, UI> (screen, ui));
}
	