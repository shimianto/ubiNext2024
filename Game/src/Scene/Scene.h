#pragma once
#include "./Managers/EntityManager/EntityManager.h"
#include "../Renderer/Renderer.h"
#include "../InputHandler/InputHandler.h"

class UIManager;

enum SceneType
{
    MENU_SCENE,
    MAIN_SCENE,
    GRID_TEST
};

class Scene
{
  protected:
  
      SceneType m_activeScene;
  
      EntityManager m_entityManager;
      Renderer m_renderer;
      InputHandler m_inputHandler;

      UIManager *m_uiManager;
  
      void SetMainScene();
      void SetMenuScene();
      void UpdateScreen();
      void RenderScreen();

  public:
      Scene ();
      void Init (UIManager &uiManager);
      void Update(float deltaTime);
      void Render();
      void Shutdown();

      SceneType GetOpenedScene();
      void SetScene (SceneType type);

      BaseEntity GetEntityFromID (int id);
      std::set<int> GetActiveEntities() const;

      const SceneType GetActiveScene() const;
};
