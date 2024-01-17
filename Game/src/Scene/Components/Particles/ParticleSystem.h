#pragma once
#include "Particle.h"
#include "../../Pool/Pool.h"

class ParticleSystem
{
  private:

	  Pool<Particle> particlePool_;

  public:

	  void NewParticle (const Vector3 &pos);
	  void Update(float deltaTime);
      void Render();
};
