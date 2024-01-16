#include "stdafx.h"
#include "ThreadGroup.h"

void ThreadGroup::JoinAll()
{
  for (auto &thread : group) {
	thread.join();
  }
}
