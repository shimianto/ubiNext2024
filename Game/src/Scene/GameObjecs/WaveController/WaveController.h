#pragma once

class Scene;

class WaveController
{
  private:

	  int waveNum_;
  public:

      int numEnemyStart;
      int numEnemyShooterStart;

      int maxEnemies;
      int maxEnemyShooters;
      
      int enemiesIncrement;

      WaveController();

      void Init (Scene &scene, int numEnemyStart = 2, int numEnemyShooterStart = 0, int maxEnemies = 5, int maxEnemyShooters = 2, int enemiesIncrement = 1);
      
      bool IsWaveDone (Scene &scene);

      void StartNextWave (Scene &scene);
};
