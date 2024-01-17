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

  BaseEntity newEntity;
  newEntity.mesh.LoadTrianglesFromObjectFile (".\\TestData\\mountains.obj");

  m_entityManager.RegisterEntity (newEntity);
}

void Scene::SetMenuScene()
{
  BaseEntity newEntity;
  newEntity.mesh.LoadTrianglesFromObjectFile (".\\TestData\\teapot.obj");

  m_entityManager.RegisterEntity (newEntity);
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


