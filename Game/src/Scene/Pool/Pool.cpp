#include "stdafx.h"
#include "Pool.h"
#include <assert.h>

template <class T> Pool<T>::Pool (int maxSize) : maxPoolSize_(maxSize)
{

}

template <class T> void Pool<T>::DisableElement (const int &id)
{
  assert(!available_.count (id));

  available_.insert (id);
  inUse_.erase (id);
}

template <class T> T Pool<T>::InstantiateNextAvailable()
{
  if (available_.size() == 0) {

	  if (poolSize_ >= maxPoolSize_) {
		  return NULL;
	  }

	pool_.push_back (T());
	inUse_.insert (poolSize_);
	poolSize_++;

	return pool_[poolSize_ - 1];
  }

  int id = *available_.cbegin();

  available_.erase (id);
  inUse_.insert (id);

  return pool_[id];
}