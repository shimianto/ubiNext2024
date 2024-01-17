#include "stdafx.h"
#include "ComponentManager.h"

ComponentManager::~ComponentManager()
{
  ClearComponents();
}

void ComponentManager::InstantiateComponents (const int &id)
{
  assert (id == m_nextValidIndex);

  m_meshComponents.push_back (Mesh());
  m_healthComponents.push_back (Health());
  m_transformComponents.push_back (Transform());

  m_nextValidIndex++;
}

Mesh &ComponentManager::GetMeshFromID (const int &id)
{
  return m_meshComponents[id];
}

Health &ComponentManager::GetHealthFromID (const int &id)
{
  return m_healthComponents[id];
}

Transform &ComponentManager::GetTransformFromID (const int &id)
{
  return m_transformComponents[id];
}

void ComponentManager::ClearComponents()
{
  m_meshComponents.clear();
  m_healthComponents.clear();
  m_transformComponents.clear();

  m_nextValidIndex = 0;
}
