#pragma once
#include "../../../Math/Triangle/Triangle.h"
#include "../Transform/Transform.h"
#include "../../../Graphics3D/Color/Color.h"
#include "../Mesh/Mesh.h"

class Particle
{
  public:
  
      static Color DEFAULT_PARTICLE_COL;
	  
      Triangle triangle2D;
      Transform transform;
      Vector3 velocity;
      Color color;

      float lifeTime;

      Particle ();
      bool animate();
};
