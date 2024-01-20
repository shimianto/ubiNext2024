#include "stdafx.h"
#include "Health.h"

int Health::GetValue()
{
  return health_;
}

const int Health::GetMax()
{
  return maxHealth_;
}

void Health::SetHealth (int health)
{
  health_ = health;
  maxHealth_ = health;
}

void Health::TakeDamage (int dmg)
{
  health_ -= dmg;
}
