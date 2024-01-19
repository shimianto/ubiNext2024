#include "stdafx.h"
#include "EntityManager.h"
#include "../../BaseEntity/BaseEntity.h"

EntityManager::EntityManager() : nextValidId_(0)
{
}

EntityManager::~EntityManager()
{
  ClearEntities();
}

int EntityManager::InstantiateNewEntity ()
{
  BaseEntity entity;
  entity.id_ = nextValidId_;
  entities_.push_back(entity);
  activeEntities_.insert (entity.id_);

  nextValidId_++;
  return entity.id_;
}

BaseEntity &EntityManager::GetEntityFromID (const int &id)
{
  return entities_[id];
}

const std::set<int> EntityManager::GetActiveEntities() const
{
  return activeEntities_;
}

void EntityManager::ClearEntities()
{
  entities_.clear();
  activeEntities_.clear();

  nextValidId_ = 0;
}
