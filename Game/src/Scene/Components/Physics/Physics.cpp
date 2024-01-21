#include "stdafx.h"
#include "Physics.h"

const Vector3 Physics::ENVIRONMENT_UPPER_BOUDS = Vector3 (45, 35);
const Vector3 Physics::ENVIRONMENT_LOWER_BOUDS = Vector3 (-45, -25);

Physics::Physics() : bounceSFX (false), gravity (false), gravityForce (0.3), drag (0), velocity (Vector3())
{
}
