#include "stdafx.h"
#include "BaseEntity.h"

BaseEntity::BaseEntity () : 
	id_(-1),
	isActive_ (true)
{
}

int BaseEntity::GetId()
{
  return id_;
}

bool BaseEntity::IsActive()
{
  return isActive_;
}

void BaseEntity::SetActive (bool active)
{
  isActive_ = active;
}
