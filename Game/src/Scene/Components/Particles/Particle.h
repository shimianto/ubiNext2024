#pragma once
#include "../../../Math/Triangle/Triangle.h"
#include "../Transform/Transform.h"
#include "../../../Graphics3D/Color/Color.h"

class Particle
{
  public:
  
      static Color DEFAULT_PARTICLE_COL;
	  
      Triangle tri;
      Vector3 position;
      Vector3 velocity;
      Color color;

      float lifeTime;

      Particle ();
      bool animate();
};
