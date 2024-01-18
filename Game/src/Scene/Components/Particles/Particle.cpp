#include "stdafx.h"
#include "Particle.h"

Color Particle::DEFAULT_PARTICLE_COL = Color (0.8f, 0, 0.6f);


Particle::Particle () : 
	tri(Triangle (Vector3(), Vector3(0,20,0), Vector3(20,10))), 
	color (DEFAULT_PARTICLE_COL),
	lifeTime (100)
{
}

bool Particle::animate()
{
  lifeTime--;
  position.x += velocity.x;
  position.y += velocity.y;

  return lifeTime <= 0;
}
