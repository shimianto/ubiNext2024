#pragma once
#include <vector>
#include <set>

template <class T>
class Pool
{
  private:
  
	  int maxPoolSize_;
	  int poolSize_;
	  std::vector<T> pool_;
      std::set<int> inUse_;
      std::set<int> available_;

  public:

	  Pool (int maxSize = 100);
	  void DisableElement (const int &id);
	  T InstantiateNextAvailable();
};
