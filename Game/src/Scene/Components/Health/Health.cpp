#include "stdafx.h"
#include "Health.h"

int Health::GetValue()
{
  return m_health;
}

void Health::SetHealth (int health)
{
  m_health = health;
}

void Health::TakeDamage (int dmg)
{
  m_health -= dmg;
}
