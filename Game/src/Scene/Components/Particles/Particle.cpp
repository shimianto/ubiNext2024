#include "stdafx.h"
#include "Particle.h"

Color Particle::DEFAULT_PARTICLE_COL = Color (0.208f, 0.968f, 0.6f, 0);


Particle::Particle () : 
	triangle2D(Triangle (Vector3(), Vector3(0,20,0), Vector3(20,10))), 
	color (DEFAULT_PARTICLE_COL),
	lifeTime (100)
{
}

bool Particle::animate()
{
  lifeTime--;
  transform.position.x += velocity.x;
  transform.position.y += velocity.y;

  return lifeTime <= 0;
}
