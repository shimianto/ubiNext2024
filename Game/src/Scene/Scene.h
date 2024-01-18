#pragma once
#include "./Managers/EntityManager/EntityManager.h"
#include "../Renderer/Renderer.h"
#include "../InputHandler/InputHandler.h"
#include "Managers/ComponentManager/ComponentManager.h"
#include "Components/Particles/ParticleSystem.h"

class UIManager;

enum SceneType
{
    MENU_SCENE,
    MAIN_SCENE,
    GRID_TEST,
    PARTICLES_SCENE
};

class Scene
{
  private:
  
      SceneType activeScene_;
  
      EntityManager entityManager_;
      
      UIManager *uiManager_;
      Renderer renderer_;
      InputHandler inputHandler_;

  public:

      ComponentManager components;

      Scene ();
      void Init (UIManager &uiManager, const SceneType &sceneType = MENU_SCENE);
      void Update(float deltaTime);
      void Render();
      void Shutdown();

      SceneType GetOpenedScene();
      void SetScene (const SceneType &type);

      int InstantiateNewEntity();
      BaseEntity GetEntityFromID (int id);
      std::set<int> GetActiveEntities() const;

      const SceneType GetActiveScene() const;
};
