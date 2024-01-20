#pragma once
#include "../../../Math/Vector3/Vector3.h"

class Physics
{
  private:
  public:
      static const Vector3 ENVIRONMENT_UPPER_BOUDS;
      static const Vector3 ENVIRONMENT_LOWER_BOUDS;
  
	  bool gravity;
      float gravityForce;
      float drag;
      Vector3 velocity;

      Physics();
};
