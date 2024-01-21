#include "stdafx.h"
#include "UIManager.h"
#include "../../UI/UI.h"
#include "../../Scene.h"

void UIManager::Init (const Scene &scene)
{
  UI menuUI;

  menuUI.InsertNewBar (UIBar (Vector3 (0, 500), Vector3 (APP_VIRTUAL_WIDTH, 300), 1, Color ()));

  menuUI.InsertNewText (UIText (Vector3 (450, 600), "Hit here to play", Color(0,0,0)));

  menuUI.InsertNewText (UIText (Vector3 (20, 470), "Space / Right trigger to charge", Color(), GLUT_BITMAP_9_BY_15));
  menuUI.InsertNewText (UIText (Vector3 (20, 450), "Release to shoot", Color(), GLUT_BITMAP_9_BY_15));
  menuUI.InsertNewText (UIText (Vector3 (20, 400), "A&D / Left stick to aim", Color(), GLUT_BITMAP_9_BY_15));

  menuUI.InsertNewText (UIText (Vector3 (750, 450), "Hit all blue for next wave", Color(), GLUT_BITMAP_9_BY_15));
  menuUI.InsertNewText (UIText (Vector3 (750, 400), "Avoid red and pink", Color(), GLUT_BITMAP_9_BY_15));
  menuUI.InsertNewText (UIText (Vector3 (750, 350), "Have fun! :)", Color(), GLUT_BITMAP_9_BY_15));
  
  RegisterUI (MENU_SCENE, menuUI);
  
  UI mainGameUI;
  RegisterUI (MAIN_SCENE, mainGameUI);

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
	