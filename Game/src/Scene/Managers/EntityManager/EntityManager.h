#pragma once
#include <vector>
#include <set>

#include "../../BaseEntity/BaseEntity.h"

class EntityManager
{
  friend class EntityManagerTest;
  private:
  
	  int nextValidId_;
      std::vector<BaseEntity> entities_; // TODO Object pooling
      std::set<int> activeEntities_;

  public:
      EntityManager();
      ~EntityManager();

      int InstantiateNewEntity ();
      BaseEntity &GetEntityFromID (const int &id);

      const std::set<int> GetActiveEntities() const;
      void ClearEntities();
};
