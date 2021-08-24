#include "Restaurant.h"





Table::Table(const int amount_of_sits,Restaurant* res)
	: kAmountOfSits_(amount_of_sits)
{
	this->my_restaurant_ = res;
	this->current_group_ = nullptr;
}

int Table::GetAmountOfSits()
{
	return kAmountOfSits_;
}

Group * Table::GetCurrentGroup()
{
	return current_group_;
}

void Table::SetCurrentGroup(Group * group)
{
	

	current_group_ = group;
	if (group != nullptr) {
		group->SetWaitingTime(my_restaurant_->GetClock());
		/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Setting grupe at table " << this->GetAmountOfSits() << " seats" << std::endl;
	}
}
