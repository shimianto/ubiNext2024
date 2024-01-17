#pragma once
#include "Particle.h"
#include "../../Pool/Pool.h"

class ParticleSystem
{
  private:

	  Pool<Particle> particlePool_;

  public:

	  void NewParticle(Transform t);
	  void Update(float deltaTime);
      void Render();
};
