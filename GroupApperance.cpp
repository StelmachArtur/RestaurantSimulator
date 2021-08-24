#include "Restaurant.h"
class Group;
void GroupApperance::Execute(int clock)
{
	
	int my_rand = rand() % 2;
	if (my_rand == 0) {
		my_restaurant_->groups_.push_back(Group(my_restaurant_,false));
		my_restaurant_->PushBuffetGroup(&*(my_restaurant_->groups_.rbegin()));
		(*(my_restaurant_->groups_.rbegin())).SetAtQueue(true);
		//[DEBUG]my_restaurant_->buffet_queue_lengths_<<my_restaurant_->GetBuffetQueue().size()<<"\n";
		//[DEBUG]my_restaurant_->buffet_queue_time_ << my_restaurant_->GetClock() << "\n";
		/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Group appears and choses buffet. Queue to buffet is equal to:  " << my_restaurant_->GetBuffetQueue().size() << std::endl;

	}
	else{
		my_restaurant_->groups_.push_back(Group(my_restaurant_, true));
		my_restaurant_->PushTableGroup(&*(my_restaurant_->groups_.rbegin()));
		(*(my_restaurant_->groups_.rbegin())).SetAtQueue(true);
		//[DEBUG]my_restaurant_->tables_queue_lengths_ << my_restaurant_->GetTableQueue().size() << "\n";
		//[DEBUG]my_restaurant_->tables_queue_time_ << my_restaurant_->GetClock() << "\n";
		/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Group appears and choses tables. Queue to tables is equal to:: " << my_restaurant_->GetTableQueue().size() << std::endl;
	}
	//[DEBUG]my_restaurant_->system_groups_amount_ << my_restaurant_->groups_.size()<<"\n";
	//[DEBUG]my_restaurant_->system_groups_times_ << my_restaurant_->GetClock() << "\n";
	my_restaurant_->AddEventToList(new GroupApperance(my_restaurant_,my_restaurant_->GetClock()+ my_restaurant_->normalDist(180, 50)));
}

GroupApperance::GroupApperance(Restaurant * res, int exe):my_restaurant_(res)
{
	this->execute_time_ = exe;
}
