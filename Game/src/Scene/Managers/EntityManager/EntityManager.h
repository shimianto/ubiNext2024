#pragma once
#include <vector>
#include <set>

#include "../../BaseEntity/BaseEntity.h"

class EntityManager
{
  private:
  
	  int nextValidId_;
      std::vector<BaseEntity> entities_;
      std::set<int> activeEntities_;

  public:
      EntityManager();
      ~EntityManager();

      int InstantiateNewEntity ();
      BaseEntity &GetEntityFromID (const int &id);

      const std::set<int> GetActiveEntities() const;
      void ClearEntities();
};
