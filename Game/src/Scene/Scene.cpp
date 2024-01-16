#include "Scene.h"
#include <list>
#include "stdafx.h"
#include "../Graphics3D/Mesh/Mesh.h"
#include "../Renderer/Renderer.h"
#include "../InputHandler/InputHandler.h"

Scene::Scene()
{
}

void Scene::Init ()
{
  m_inputHandler.Init (*this);
  m_renderer.Init (*this);
}

void Scene::Update (float deltaTime)
{
  UpdateScreen();
  m_inputHandler.HandleInput (deltaTime);
  m_renderer.Update (deltaTime);
}

void Scene::Render()
{
  RenderScreen();
  m_renderer.Render();
}

void Scene::Shutdown()
{
}

ScreenType Scene::GetScreen()
{
  return m_screenOnDisplay;
}

void Scene::SetScreen (ScreenType type)
{
  m_entityManager.ClearEntities();
  m_screenOnDisplay = type;
  switch (type) {
  case MENU_SCREEN:
	SetMenuScene();
	break;
  case MAIN_SCREEN:
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

void Scene::SetMainScene()
{
  Camera::mainCamera = Camera();

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
  switch (m_screenOnDisplay) {
  case MENU_SCREEN:
	Camera::mainCamera.fXaw += 0.005;
	Camera::mainCamera.fZaw += 0.005;
	break;
  case MAIN_SCREEN:
	break;
  default:
	break;
  }
}

void Scene::RenderScreen()
{
  switch (m_screenOnDisplay) {
  case MENU_SCREEN:
	App::Print (450, 700, "Menu: Ubi Next 2024", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
	break;
  case MAIN_SCREEN:
	App::Print (450, 700, "Main Scene", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
	break;
  default:
	break;
  }
}


