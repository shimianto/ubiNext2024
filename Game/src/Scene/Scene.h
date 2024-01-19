#pragma once
#include "./Managers/EntityManager/EntityManager.h"
#include "../Renderer/Renderer.h"
#include "../InputHandler/InputHandler.h"
#include "Managers/ComponentManager/ComponentManager.h"
#include "Components/Particles/ParticleSystem.h"
#include "GameObjecs/Player/Player.h"
#include "GameObjecs/Bullet/Bullet.h"
#include "GameObjecs/Enemy/Enemy.h"

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

      //Game Objects
      Player player_;
      Pool<Bullet> bullets_;
      Pool<Enemy> enemies_;

  public:

      ComponentManager components;

      //Game Objects
      //int playerId;
      //std::set<int> enemyObjs;



      Scene ();
      void Init (UIManager &uiManager, const SceneType &sceneType = MENU_SCENE);
      void Update(float deltaTime);
      void Render();
      void Shutdown();

      const SceneType GetActiveScene() const;

      const int InstantiateNewEntity();
      BaseEntity GetEntityFromID (int id);
      std::set<int> GetActiveEntities() const;

      //Get game Objecs
      void SetPlayer(Player &player);
      Player &GetPlayer();
      Pool<Bullet> &GetBullets();
      Pool<Enemy> &GetEnemies();

      void SetScene (const SceneType &type);
};
