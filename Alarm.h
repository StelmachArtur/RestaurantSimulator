#pragma once
#include "Event.h"
class Restaurant;
class Alarm : public Event {
public: 
	explicit Alarm(Restaurant* res);
	void Execute(int clock) override;
private:
	Restaurant* my_restaurant_;
};