#pragma once
#include "Particle.h"
#include "../../Pool/Pool.h"

class ParticleSystem
{
  private:

	  Pool<Particle> particlePool_;

  public:

	  void NewParticle (const Vector3 &pos, const Color &col = Particle::DEFAULT_PARTICLE_COL);
      void Update (const float &deltaTime);
      void Render();
      bool HasActiveParticles();
};
