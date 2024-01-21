#pragma once
class Scene;

class InputHandler
{
  private:
    
      Scene *scene_;

      void HandleMainSceneInput (float deltaTime);
      void HandleMenuSceneInput (float deltaTime);
      void HandleParticleSceneInput(float deltaTime);

  public:
  
      void Init (Scene &scene);
      void HandleInput (float deltaTime);
};
