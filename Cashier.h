#pragma once
#include "Waiter.h"

class Cashier :public Event
{
public:

	explicit Cashier(Restaurant* res);
	void Execute(int clock);
	Group* GetCurrent();
	void SetCashierCurrent(Group* grp);
	int GetId();
protected:
	//[DEBUG]std::string stats;
	int id_;	//id of group
	Restaurant* my_restaurant_;
	static int index_;  //truck of ids
	Group* current_; // pointer on Group that is currently served
};
 