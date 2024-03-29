#pragma once
#include "../Renderer/Renderer.h"
#include "../InputHandler/InputHandler.h"
#include "Managers/ComponentManager/ComponentManager.h"
#include "Managers/EntityManager/EntityManager.h"
#include "Components/Particles/ParticleSystem.h"
#include "GameObjecs/Player/Player.h"
#include "GameObjecs/Bullet/Bullet.h"
#include "GameObjecs/Enemy/Enemy.h"
#include "GameObjecs/EnemyShooter/EnemyShooter.h"
#include "GameObjecs/WaveController/WaveController.h"
#include "GameObjecs/Button/Button.h"

class UIManager;

enum SceneType
{
    MENU_SCENE,
    MAIN_SCENE
};

class Scene
{
  private:
  
      SceneType activeScene_;
  
      EntityManager entityManager_;
      
      Renderer renderer_;
      InputHandler inputHandler_;

      //Game Objects
      Player player_;
      Pool<Bullet> bullets_;
      Pool<Enemy> enemies_;
      Pool<EnemyShooter> enemyShooters_;
      Pool<Button> buttons_;

      void UpdatePlayer (float &deltaTime);
      void UpdateEnemies (float &deltaTime);
  public:

      UIManager *uiManager_;
      ComponentManager components;

      //Game Objects
      //int playerId;
      //std::set<int> enemyObjs;



      Scene ();
      void Init (UIManager &uiManager, const SceneType &sceneType = MENU_SCENE);
      void Update (float deltaTime);
      void UpdateParticles (float &deltaTime);
      void TryButtons();
      void UpdateBullets (float &deltaTime);
      void UpdateEnemyShooters (float &deltaTime);
      void Render();
      void Shutdown();

      const SceneType GetActiveScene() const;

      const int InstantiateNewEntity();
      BaseEntity GetEntityFromID (int id);
      std::set<int> GetActiveEntities() const;
      void EnableEntity (const int &id);
      void DisableEntity (const int &id);

      //Get Game Objecs
      void SetPlayer(Player &player);
      Player &GetPlayer();
      Pool<Bullet> &GetBullets();
      Pool<Enemy> &GetEnemies();
      Pool<EnemyShooter> &GetEnemyShooters();
      Pool<Button> &GetButtons();
      WaveController waveController;

      void SetScene (const SceneType &type);
      void ClearGameObjects();
};
