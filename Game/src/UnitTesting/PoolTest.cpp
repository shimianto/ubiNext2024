#pragma once
#include "stdafx.h"
#include"../Scene/Pool/Pool.h"

class TemplateClass
{

};

class PoolTest
{
  public:
	  static void Run()
	  {
	    Pool<TemplateClass> pool(5), poolFull(5), poolWithAvailable(5);

	    pool.InstantiateNextAvailable();
	    pool.InstantiateNextAvailable();
	    pool.InstantiateNextAvailable();
	    pool.InstantiateNextAvailable();

	    poolFull.InstantiateNextAvailable();
	    poolFull.InstantiateNextAvailable();
	    poolFull.InstantiateNextAvailable();
	    poolFull.InstantiateNextAvailable();
	    poolFull.InstantiateNextAvailable();

	    poolWithAvailable.InstantiateNextAvailable();
	    poolWithAvailable.InstantiateNextAvailable();
	    poolWithAvailable.InstantiateNextAvailable();
	    poolWithAvailable.InstantiateNextAvailable();
	    poolWithAvailable.DisableElement(2);


		TestConstructor ();
	    TestDisableElement (pool, 2);
	    TestInstantiateNextAvailable (pool);
	    TestInstantiateNextAvailableWhenPoolIsFull (poolFull);
	    TestInstantiateNextAvailableWhenThereIsElementAvailable (poolWithAvailable);
	    TestGetInUseElements (poolWithAvailable);
	  }

  private:
      static void TestConstructor()
      {
	    Pool<TemplateClass> pool(5);
	    assert (pool.maxPoolSize_ == 5);
	    assert (pool.poolSize_ == 0);
	    assert (pool.pool_.size() == 0);
	    assert (pool.available_.size() == 0);
	    assert (pool.inUse_.size() == 0);
      }


	  static void TestDisableElement (Pool<TemplateClass> pool, const int &id)
      {
	    pool.DisableElement (id);

		assert (pool.maxPoolSize_ == 5);
	    assert (pool.poolSize_ == 4);
	    assert (pool.pool_.size() == 4);

	    assert (pool.available_.size() == 1);
	    assert (pool.inUse_.size() == 3);

	    assert (pool.available_.count (id));
	    assert (!pool.inUse_.count (id));
      }
		 
	  static void TestInstantiateNextAvailable (Pool<TemplateClass> pool)
      {
	    assert (pool.maxPoolSize_ == 5);
	    assert (pool.poolSize_ == 4);
	    assert (pool.pool_.size() == 4);
	    assert (pool.available_.size() == 0);
	    assert (pool.inUse_.size() == 4);

		int newId;
	    
		newId = pool.InstantiateNextAvailable();

		assert (newId == 4);

		assert (pool.maxPoolSize_ == 5);
	    assert (pool.poolSize_ == 5);
	    assert (pool.pool_.size() == 5);
	    assert (pool.available_.size() == 0);
	    assert (pool.inUse_.size() == 5);
      }

	  static void TestInstantiateNextAvailableWhenPoolIsFull (Pool<TemplateClass> pool)
      {
	    assert (pool.maxPoolSize_ == 5);
	    assert (pool.poolSize_ == 5);

	    int newId = pool.InstantiateNextAvailable();

	    assert (newId == -1);

	    assert (pool.maxPoolSize_ == 5);
	    assert (pool.poolSize_ == 5);
	    assert (pool.pool_.size() == 5);
	    assert (pool.available_.size() == 0);
	    assert (pool.inUse_.size() == 5);
      }

	  
	  static void TestInstantiateNextAvailableWhenThereIsElementAvailable (Pool<TemplateClass> pool)
      {

	    assert (pool.maxPoolSize_ == 5);
	    assert (pool.poolSize_ == 4);
	    assert (pool.pool_.size() == 4);
	    assert (pool.available_.size() == 1);
	    assert (pool.inUse_.size() == 3);

	    int newId = pool.InstantiateNextAvailable();

	    assert (newId == 2);

	    assert (pool.maxPoolSize_ == 5);
	    assert (pool.poolSize_ == 4);
	    assert (pool.pool_.size() == 4);
	    assert (pool.available_.size() == 0);
	    assert (pool.inUse_.size() == 4);
      }

	  static void TestGetInUseElements (Pool<TemplateClass> &pool)
      {
	    auto inUseElements = pool.GetInUseElements();

		assert (pool.inUse_.size() == 3);
	    assert (pool.inUse_.count (0));
	    assert (pool.inUse_.count (1));
	    assert (pool.inUse_.count (3));
	  }
};