#pragma once
class Scene;

class InputHandler
{
  private:
    
      Scene *m_Scene;

      void HandleMainSceneInput (float deltaTime);
      void HandleMenuSceneInput (float deltaTime);

  public:
  
      void Init (Scene &scene);
      void HandleInput (float deltaTime);
      void HandleParticleSceneInput();
};
