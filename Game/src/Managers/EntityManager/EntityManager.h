#pragma once
#include <vector>
#include <set>

#include "BaseEntity.h"

class EntityManager
{
  private:
  
	  static int s_nextValidId;
      std::vector<BaseEntity> m_entities;
      std::set<int> m_activeEntities;
      std::set<int> m_inactiveEntities;

  public:
      EntityManager();
      ~EntityManager();

      int RegisterEntity (BaseEntity &entity);
      BaseEntity &GetEntityFromID (int id);
      const std::set<int> GetActiveEntities() const;
      void ClearEntities();
};
