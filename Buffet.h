#pragma once
#include "Group.h"

class Buffet
{
public:
	explicit Buffet(int buffet_capacity,Restaurant* res);
	void SetSpots(int seats);
	int GetSpots();
	void PushToBuffetList(Group* grp);
	void RemoveFromBuffet(Group* grp);
private:
	const int kBuffetCapacity_; // capacity of the buffet

	Restaurant* my_restaurant_;
	int spots_;			//actual free spots in buffet
	std::list<Group*> current_;  // vector of pointers on groups that are currently served

};