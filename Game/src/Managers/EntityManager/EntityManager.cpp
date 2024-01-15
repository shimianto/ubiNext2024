#include "stdafx.h"
#include "EntityManager.h"
#include "BaseEntity.h"


int EntityManager::s_nextValidId = 0;

EntityManager::EntityManager()
{
}

int EntityManager::RegisterEntity (BaseEntity &entity)
{
  assert (entity.m_id <= s_nextValidId);

  entity.m_id = s_nextValidId;
  m_entities.push_back (entity);
  s_nextValidId++;

  return entity.m_id;
}

void EntityManager::UnregisterEntity (BaseEntity entity)
{
}


BaseEntity EntityManager::GetEntityFromID (int id)
{
  return m_entities[id];
}
