#pragma once
#include "Table.h"


class Waiter:public Event
{
public:
	explicit Waiter(Restaurant* res);
	void Execute(int clock);
	Group* GetWaiterCurrent();
	void SetWaiterCurrent(Group* busy);	
	//[DEBUG]std::string stats;

private:
	static int index_;
	int id_;
	Restaurant* my_restaurant_;
	Group* current_;
};

