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
      int RegisterEntity (BaseEntity &entity);
      void UnregisterEntity (BaseEntity entity);
      BaseEntity GetEntityFromID (int id);
};
