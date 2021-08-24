#pragma once
#include "Buffet.h"

class Table
{
public:
	explicit Table(const int amount_of_sits,Restaurant* res);
	int GetAmountOfSits();
	Group* GetCurrentGroup();
	void SetCurrentGroup(Group* group);

private:
	const int kAmountOfSits_; // amount of sits of particural table
	Restaurant* my_restaurant_;
	Group* current_group_;	//pointer on current sitting group

};
