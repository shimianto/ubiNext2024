#pragma once
class Health
{
  private:
  
	  int health_;
      int maxHealth_;

  public:

	  int GetValue();
      const int GetMax();
      void SetHealth(int health);
      void TakeDamage (int dmg);
};
