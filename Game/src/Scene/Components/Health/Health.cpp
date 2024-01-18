#include "stdafx.h"
#include "Health.h"

int Health::GetValue()
{
  return health_;
}

void Health::SetHealth (int health)
{
  health_ = health;
}

void Health::TakeDamage (int dmg)
{
  health_ -= dmg;
}
