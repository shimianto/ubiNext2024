#include "stdafx.h"
#include "EntityManager.h"
#include "../../BaseEntity/BaseEntity.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
  ClearEntities();
}

int EntityManager::RegisterEntity (BaseEntity entity)
{
  entity.m_id = m_nextValidId;
  m_entities.push_back(entity);
  m_activeEntities.insert (entity.m_id);

  m_nextValidId++;
  return entity.m_id;
}

BaseEntity &EntityManager::GetEntityFromID (const int &id)
{
  return m_entities[id];
}

const std::set<int> EntityManager::GetActiveEntities() const
{
  return m_activeEntities;
}

void EntityManager::ClearEntities()
{
  m_entities.clear();
  m_activeEntities.clear();
  m_inactiveEntities.clear();

  m_nextValidId = 0;
}
