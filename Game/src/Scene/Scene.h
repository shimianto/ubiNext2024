#pragma once
#include "../Managers/EntityManager/EntityManager.h"
#include "../Renderer/Renderer.h"
#include "../InputHandler/InputHandler.h"

enum ScreenType
{
    MENU_SCREEN,
    MAIN_SCREEN
};

class Scene
{
  protected:
  
      ScreenType m_screenOnDisplay;
  
      EntityManager m_entityManager;
      Renderer m_renderer;
      InputHandler m_inputHandler;
  
      void SetMainScene();
      void SetMenuScene();
      void UpdateScreen();
      void RenderScreen();

  public:
      Scene();
      void Init ();
      void Update(float deltaTime);
      void Render();
      void Shutdown();

      ScreenType GetScreen();
      void SetScreen (ScreenType type);

      BaseEntity GetEntityFromID (int id);
      std::set<int> GetActiveEntities() const;
};
