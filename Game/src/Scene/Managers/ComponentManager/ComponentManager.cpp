#include "stdafx.h"
#include "ComponentManager.h"

ComponentManager::~ComponentManager()
{
  ClearComponents();
}

void ComponentManager::InstantiateComponents (const int &id)
{
  assert (id == nextValidIndex_);

  meshComponents_.push_back (Mesh());
  healthComponents_.push_back (Health());
  transformComponents_.push_back (Transform());
  particlesComponents_.push_back (ParticleSystem());

  nextValidIndex_++;
}

Mesh &ComponentManager::GetMeshFromID (const int &id)
{
  return meshComponents_[id];
}

Health &ComponentManager::GetHealthFromID (const int &id)
{
  return healthComponents_[id];
}

Transform &ComponentManager::GetTransformFromID (const int &id)
{
  return transformComponents_[id];
}

ParticleSystem &ComponentManager::GetParticlesFromID (const int &id)
{
  return particlesComponents_[id];
}

void ComponentManager::ClearComponents()
{
  meshComponents_.clear();
  healthComponents_.clear();
  transformComponents_.clear();
  particlesComponents_.clear();

  nextValidIndex_ = 0;
}
