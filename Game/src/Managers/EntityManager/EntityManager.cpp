#include "stdafx.h"
#include "EntityManager.h"
#include "BaseEntity.h"


int EntityManager::s_nextValidId = 0;

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
  ClearEntities();
}

int EntityManager::RegisterEntity (BaseEntity &entity)
{
  assert (entity.m_id <= s_nextValidId);

  entity.m_id = s_nextValidId;
  m_entities.push_back (entity);
  s_nextValidId++;

  return entity.m_id;
}

BaseEntity EntityManager::GetEntityFromID (int id)
{
  return m_entities[id];
}

void EntityManager::ClearEntities()
{
  m_entities.clear();
  s_nextValidId = 0;
}
