#pragma once
#include "../../../Math/Triangle/Triangle.h"
#include "../Transform/Transform.h"
class Particle
{
  public:

	  Triangle tri;
      Transform transform;
      Vector3 velocity;

      float lifeTime;

      Particle ();
      bool animate();
};
