#include "stdafx.h"
#include "Particle.h"

Particle::Particle () : 
	tri(Triangle (Vector3(), Vector3(0,20,0), Vector3(20,10))),
	lifeTime(100)
{
}

bool Particle::animate()
{
  lifeTime--;
  position.x += velocity.x;
  position.y += velocity.y;

  return lifeTime <= 0;
}
