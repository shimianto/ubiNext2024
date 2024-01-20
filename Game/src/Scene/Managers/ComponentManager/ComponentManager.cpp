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
  gridComponents_.push_back (Grid());
  baseAIComponents_.push_back (BaseAI());
  colliderComponents_.push_back (Collider());

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

Grid &ComponentManager::GetGridFromID (const int &id)
{
  return gridComponents_[id];
}

BaseAI &ComponentManager::GetAIFromID (const int &id)
{
  return baseAIComponents_[id];
}

Collider &ComponentManager::GetColliderFromID (const int &id)
{
  return colliderComponents_[id];
}

void ComponentManager::ClearComponents()
{
  meshComponents_.clear();
  healthComponents_.clear();
  transformComponents_.clear();
  particlesComponents_.clear();
  gridComponents_.clear();
  baseAIComponents_.clear();
  colliderComponents_.clear();

  nextValidIndex_ = 0;
}
