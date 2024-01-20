#pragma once
#include <vector>
#include <set>

template <class T>
class Pool
{
  friend class PoolTest;
  private:
  
	  int maxPoolSize_;
	  int poolSize_;
	  std::vector<T> pool_;
      std::set<int> inUse_;
      std::set<int> available_;

  public:

	  Pool (int maxSize = 100);
	  void DisableElement (const int &id);
	  int InstantiateNextAvailable();
      T &GetElementByID (const int &id);
      const std::set<int> &GetInUseElements() const;
};

template <class T> Pool<T>::Pool (int maxSize) : maxPoolSize_ (maxSize), poolSize_(0)
{
}

template <class T> void Pool<T>::DisableElement (const int &id)
{
      assert (!available_.count (id));

      available_.insert (id);
      inUse_.erase (id);
}

template <class T> int Pool<T>::InstantiateNextAvailable()
{
      if (available_.size() == 0) {

	    if (poolSize_ >= maxPoolSize_) {
	      return -1;
	    }

	    pool_.push_back (T());
	    inUse_.insert (poolSize_);
	    poolSize_++;

	    return poolSize_ - 1;
      }

      int id = *available_.cbegin();

      available_.erase (id);
      inUse_.insert (id);

      return id;
}

template <class T> T &Pool<T>::GetElementByID (const int &id)
{
      assert (id >= 0 && id < poolSize_);

      return pool_[id];
}

template <class T> const std::set<int> &Pool<T>::GetInUseElements() const
{
      return inUse_;
}
