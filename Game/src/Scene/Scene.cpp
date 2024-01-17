#include "Scene.h"
#include <list>
#include "stdafx.h"
#include "Components/Mesh/Mesh.h"
#include "../Renderer/Renderer.h"
#include "../InputHandler/InputHandler.h"
#include "Managers//UIManager/UIManager.h"

Scene::Scene()
{
}

void Scene::Init (UIManager &uiManager)
{
  m_uiManager = &uiManager;

  m_uiManager->Init(*this);

  m_inputHandler.Init (*this);
  m_renderer.Init (*this);
}


void Scene::Update (float deltaTime)
{
  m_uiManager->Update (*this);

  UpdateScreen();
  m_inputHandler.HandleInput (deltaTime);
  m_renderer.Update (deltaTime);
}

void Scene::Render()
{
  m_uiManager->Render (*this);

  RenderScreen();
  m_renderer.Render();
}

void Scene::Shutdown()
{
}

SceneType Scene::GetOpenedScene()
{
  return m_activeScene;
}

void Scene::SetScene (SceneType type)
{
  m_entityManager.ClearEntities();
  components.ClearComponents();
  m_activeScene = type;
  switch (type) {
  case MENU_SCENE:
	SetMenuScene();
	break;
  case MAIN_SCENE:
	SetMainScene();
	break;
  default:
	break;
  }
}

int Scene::InstantiateNewEntity()
{
  int entId = m_entityManager.RegisterEntity (BaseEntity());
  components.InstantiateComponents (entId);

  return entId;
}

BaseEntity Scene::GetEntityFromID (int id)
{
  return m_entityManager.GetEntityFromID(id);
}

std::set<int> Scene::GetActiveEntities() const
{
  return m_entityManager.GetActiveEntities();
}

const SceneType Scene::GetActiveScene() const
{
  return m_activeScene;
}

void Scene::SetMainScene()
{
  Camera::mainCamera.transform = Transform();

  int newEntityId = InstantiateNewEntity();
  components.GetMeshFromID(newEntityId).LoadTrianglesFromObjectFile (".\\TestData\\mountains.obj");
}

void Scene::SetMenuScene()
{
  int newEntityId = InstantiateNewEntity();
  components.GetMeshFromID (newEntityId).LoadTrianglesFromObjectFile (".\\TestData\\teapot.obj");
}

void Scene::UpdateScreen()
{
  switch (m_activeScene) {
  case MENU_SCENE:
	break;
  case MAIN_SCENE:
	break;
  default:
	break;
  }
}

void Scene::RenderScreen()
{
  switch (m_activeScene) {
  case MENU_SCENE:
	break;
  case MAIN_SCENE:
	break;
  default:
	break;
  }
}


