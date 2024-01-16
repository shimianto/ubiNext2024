#include "stdafx.h"
#include "BaseEntity.h"
#include "EntityManager.h"

BaseEntity::BaseEntity () : 
	m_id(-1),
	m_isActive (true)
{
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
