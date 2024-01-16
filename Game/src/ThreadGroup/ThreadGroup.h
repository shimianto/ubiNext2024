#pragma once
#include <vector>
#include <thread>
#include <tuple>
#include <iostream>


class ThreadGroup
{
  public:
  
	  std::vector<std::thread> group;

	  void JoinAll();
};