#pragma once
#include "Particle.h"
#include "../../Pool/Pool.h"

class ParticleSystem
{
  private:
  
      int particleLife_;
      float particlesScale_;
  public:

	  Pool<Particle> particlePool;
      Mesh mesh;

      ParticleSystem();


      void Update (const float &deltaTime);
      void Render2D();

      void SpawnParticles (const int &num, const Vector3 &pos, const Vector3 &direction, const Color &col = Particle::DEFAULT_PARTICLE_COL);
      void NewParticle (const Vector3 &pos, const Vector3 &direction, const Color &col = Particle::DEFAULT_PARTICLE_COL);
      bool HasActiveParticles();
      void SetParticleLife (const int &life);
      void SetParticleScale (const float &scale);
};
