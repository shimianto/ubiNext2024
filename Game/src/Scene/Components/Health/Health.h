#pragma once
class Health
{
  private:
  
	  int m_health;

  public:

	  int GetValue();
      void SetHealth(int health);
      void TakeDamage (int dmg);
};
