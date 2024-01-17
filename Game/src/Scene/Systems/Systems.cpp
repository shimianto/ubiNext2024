#include "stdafx.h"
#include "Systems.h"

int Systems::RandInt (int min, int max)
{
  return rand() % (max - min + 1) + min;
}

float Systems::RandFloat()
{
  return (float)rand() / (float)RAND_MAX;
}
