#pragma once
#include <vector>

class BaseEntity;

class EntityManager
{
  private:
  
	  static int s_nextValidId;
	  std::vector<BaseEntity> m_entities;

  public:
      EntityManager();
      ~EntityManager();

      int RegisterEntity (BaseEntity &entity);
      BaseEntity GetEntityFromID (int id);
      void ClearEntities();
};
