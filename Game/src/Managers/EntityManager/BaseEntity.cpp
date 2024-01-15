#include "stdafx.h"
#include "BaseEntity.h"
#include "EntityManager.h"

BaseEntity::BaseEntity (EntityManager &manager) : 
	m_isActive (true)
{
  m_id = -1;
  manager.RegisterEntity (*this);
}

int BaseEntity::GetId()
{
  return m_id;
}

bool BaseEntity::IsActive()
{
  return m_isActive;
}

void BaseEntity::SetActive (bool active)
{
  m_isActive = active;
}
