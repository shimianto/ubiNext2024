#include "stdafx.h"
#include "Utils.h"
#include "../Vector3/Vector3.h"
#include "../Matrix/Matrix.h"

int Utils::RandInt (int min, int max)
{
  return rand() % (max - min + 1) + min;
}
float Utils::RandFloat()
{
  return (float)rand() / (float)RAND_MAX;
}

float Utils::GetDistance (Vector3 &p1, Vector3 &p2)
{
  return sqrtf (
	  ((p1.x - p2.x) * (p1.x - p2.x)) + 
	  ((p1.y - p2.y) * (p1.y - p2.y)) + 
	  ((p1.z - p2.z) * (p1.z - p2.z))
  );
}
