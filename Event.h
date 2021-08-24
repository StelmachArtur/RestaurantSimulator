#pragma once
#include <vector>
#include <utility>
#include <list>
#include <random>
#include <iostream>
#include <string>
#include <fstream>
class Event {
public:

	int execute_time_;
	virtual void Execute(int clock) = 0;
};
