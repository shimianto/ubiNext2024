#pragma once
#include "stdafx.h"
#include "../Scene/Managers/EntityManager/EntityManager.h"

class EntityManagerTest
{
  public:
  static void Run()
  {
	EntityManager em;
	em.InstantiateNewEntity();
	em.InstantiateNewEntity();
	em.InstantiateNewEntity();
	em.InstantiateNewEntity();
	em.InstantiateNewEntity();

	TestConstructor();
	TestInstantiateNewEntity();
	TestGetEntityFromID (em, 3);
	TestGetActiveEntities (em);
	TestClearEntities (em);
  }

  private:
	static void TestConstructor()
	{
	  EntityManager em;

	  assert (em.nextValidId_== 0);
	  assert (em.entities_.size() == 0);
	  assert (em.activeEntities_.size() == 0);
	}

	static void TestInstantiateNewEntity()
    {
	  EntityManager em;
	  em.InstantiateNewEntity();

	  assert (em.nextValidId_ == 1);
	  assert (em.entities_.size() == 1);
	  assert (em.activeEntities_.size() == 1);
	  assert (em.entities_[0].GetId() == 0);

	  em.InstantiateNewEntity();

	  assert (em.nextValidId_ == 2);
	  assert (em.entities_.size() == 2);
	  assert (em.activeEntities_.size() == 2);
	  assert (em.entities_[1].GetId() == 1);
    }
    static void TestGetEntityFromID(EntityManager &em, const int &id)
    {
	  assert (em.entities_[id].GetId() == 3);
    }

	static void TestGetActiveEntities (EntityManager &em)
    {
	  const std::set<int> activeEntitiesID = em.GetActiveEntities();

	  assert (activeEntitiesID.size() == 5);
	  assert (activeEntitiesID.count (0));
	  assert (activeEntitiesID.count (1));
	  assert (activeEntitiesID.count (2));
	  assert (activeEntitiesID.count (3));
	  assert (activeEntitiesID.count (4));
    }

	static void TestClearEntities (EntityManager em)
    {
	  em.ClearEntities();
	  assert (em.nextValidId_ == 0);
	  assert (em.entities_.size() == 0);
	  assert (em.activeEntities_.size() == 0);
    }
};
