#pragma once
#include "Alarm.h"
class Restaurant;
class GroupApperance : public Event {
public:
	explicit GroupApperance() = default;
	explicit GroupApperance(Restaurant* res, int execute_time);
	void Execute(int clock) override;

private:
	Restaurant* my_restaurant_;

};