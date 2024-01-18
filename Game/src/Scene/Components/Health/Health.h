#pragma once
class Health
{
  private:
  
	  int health_;

  public:

	  int GetValue();
      void SetHealth(int health);
      void TakeDamage (int dmg);
};
