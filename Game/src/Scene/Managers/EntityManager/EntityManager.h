#pragma once
#include <vector>
#include <set>

#include "../../BaseEntity/BaseEntity.h"

class EntityManager
{
  private:
  
	  int m_nextValidId;
      std::vector<BaseEntity> m_entities;
      std::set<int> m_activeEntities;
      std::set<int> m_inactiveEntities;

  public:
      EntityManager();
      ~EntityManager();

      int RegisterEntity (BaseEntity entity);
      BaseEntity &GetEntityFromID (const int &id);

      const std::set<int> GetActiveEntities() const;
      void ClearEntities();
};
