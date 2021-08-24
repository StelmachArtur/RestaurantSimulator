#pragma once
#include "Cashier.h"

class RestaurantManager :public Event
{
public:
	explicit RestaurantManager(const int service_time);
	int ServiceTime() const; 
	Group* Current() const;
	void Execute(int clock);
	void SetMyRestaurant(Restaurant* restaurant);
	bool Busy();
	void SetActivationTime(int clock);
	void SetBusy(bool busy);
	std::pair<Table*, Group*> GetGroupToSeat();
private:
	const int kServiceTime_; //  service time of menager
	Restaurant* my_restaurant_;
	bool busy_;			//true if meneger is leading group to table
	Group* current_;	// pointer on current serving group
};
