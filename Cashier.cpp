#include "Restaurant.h"
Cashier::Cashier(Restaurant* res)
{
	++index_;
	this->id_ = index_;
	this->my_restaurant_ = res;
	this->current_ = nullptr;
}

void Cashier::Execute(int clock)
{
	/**/	if (my_restaurant_->GetMode() != 3)
	std::cout << "Resetting cashier id: " << this->id_<<" simulation time "<<my_restaurant_->GetClock()<<"\n";

	//[DEBUG]this->stats.append(" kasjer obsluzyl grupe i zostal zresetowany w czasie symulacji: ");
	//[DEBUG]this->stats.append(std::to_string(my_restaurant_->GetClock()));
	//[DEBUG]current_->stats.append(" Grupa zostala obsluzona przez kasjera w czasie symulacji: ");
	//[DEBUG]current_->stats.append(std::to_string(my_restaurant_->GetClock()));
	my_restaurant_->RemoveGroupFromRestaurant(this->current_);
	//[DEBUG]my_restaurant_->cashiers_data_ << this->stats << "\n";

	//[DEBUG]this->stats = "";
	this->current_ = nullptr;
}

Group * Cashier::GetCurrent()
{
	return this->current_;
}

void Cashier::SetCashierCurrent(Group * grp)
{
	if (grp != nullptr) {
		if (my_restaurant_->GetMode() != 3)
			std::cout << "Removing group id: " << grp->GroupId() << " to the cashier id: " << this->id_ << "\n";

		this->current_ = grp;
		grp->SetAtQueue(false);
		my_restaurant_->RemoveGroupFromCashierQueue(); //popping firs group in queue
		this->execute_time_ = my_restaurant_->GetClock() + my_restaurant_->expDist(1 / 1250.0);

		//[DEBUG]my_restaurant_->cashier_queue_lengths_ << my_restaurant_->GetCashierQueue().size() << "\n";
		//[DEBUG]my_restaurant_->cashier_queue_time_ << my_restaurant_->GetClock() << "\n";

		//[DEBUG]this->stats.append(std::to_string(this->id_));
		//[DEBUG]this->stats.append(" cashier got  grupe o id: ");
		//[DEBUG]this->stats.append(std::to_string(grp->GroupId()));
		//[DEBUG]this->stats.append(" simulation time: ");
		//[DEBUG]this->stats.append(std::to_string(my_restaurant_->GetClock()));
		//[DEBUG]this->stats.append(" cashier should finish service to that group: ");
		//[DEBUG]this->stats.append(std::to_string(this->execute_time_));
		//[DEBUG]current_->stats.append(" Group got cashier in: ");
		//[DEBUG]current_->stats.append(std::to_string(my_restaurant_->GetClock()));

		//[DEBUG]current_->stats.append(" Group should be stopped : ");
		//[DEBUG]current_->stats.append(std::to_string(this->execute_time_));

		my_restaurant_->AddEventToList(this);
	}
	else {
		this->current_ = nullptr;
	}
}

int Cashier::GetId()
{
	return this->id_;
}
int Cashier::index_ = 0;