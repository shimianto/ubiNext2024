#include "stdafx.h"
#include "UIManager.h"
#include "../../UI/UI.h"
#include "../../Scene.h"

void UIManager::Init (const Scene &scene)
{  
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
  uiMap_[sceneType] = ui;
}

UI &UIManager::GetActiveUI (const Scene &scene)
{
  return uiMap_[scene.GetActiveScene()];
}
	