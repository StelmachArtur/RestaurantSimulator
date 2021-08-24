#include "Restaurant.h"




bool Group::GetGoingToRun()
{
	return going_to_run_;
}

void Group::Execute(int clock) {

	if (this->to_tables_ == false) {
		if (my_restaurant_->GetMode() != 3)
			std::cout << "Execute grupy buffet o id: " << group_id_ << ". In simulation time: " << my_restaurant_->GetClock()<<"\n";
		this->bevrages_served_ = true;
	
		this->main_dish_served_ = true;
		this->ate_ = true;
		my_restaurant_->GetBuffet()->RemoveFromBuffet(this);
		my_restaurant_->PushCashierGroup(this);
		this->at_queue = true;
	}
	else {
		//[DEBUG]this->stats.append(" Grupa konczy jesc w czasie symulacji: ");
		//[DEBUG]this->stats.append(std::to_string(my_restaurant_->GetClock()));
		if (my_restaurant_->GetMode() != 3)
			std::cout << "Execute of group id: " << group_id_ << ". Group will finish eating at: " << my_restaurant_->GetClock() << "\n";
		my_restaurant_->RemoveGroupFromTables(this);
		my_restaurant_->PushCashierGroup(this);
		this->ate_ = true;
		this->at_queue = true;
		//[DEBUG]my_restaurant_->cashier_queue_lengths_ << my_restaurant_->GetCashierQueue().size() << "\n";
		//[DEBUG]my_restaurant_->cashier_queue_time_ << my_restaurant_->GetClock() << "\n";
	}
}

Group::Group(Restaurant *my_restaurant,bool totables)
	:  my_restaurant_(my_restaurant)
{
	
	this->ate_ = false;
	this->at_queue = false;
	this->being_served_ = false;
	this->to_tables_ = totables;
	++index_;
	/**/if (my_restaurant_->GetMode() != 3)
	std::cout << "Group index: " << index_ << " appears in the restaurant. Simulation time: " << my_restaurant_->GetClock()<<"\n";
	this->group_id_ = index_;
	this->bevrages_served_ = false;
	this->main_dish_served_ = false;
	
	this->waiting_time_ = my_restaurant_->GetClock();
	int my_rand = rand() % 100;
	if (my_rand <= 11) {
		this->number_of_clients_ = 1;
		/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Group has 1 person" << std::endl;
	} 
	else if(my_rand > 11 && my_rand <= 44) {
		this->number_of_clients_ = 2;
		/**/	if (my_restaurant_->GetMode() != 3)
		std::cout <<  "Group has 2 people" << std::endl;
	}
	else if (my_rand > 44 && my_rand <= 77) {
		this->number_of_clients_ = 3;
		/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Group has 3 people" << std::endl;
	}
	else {
		this->number_of_clients_ = 4;
		/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Group has 4 people" << std::endl;
	}
	my_rand = rand() % 100;
	if (my_rand < 30)
		this->going_to_run_ = true;
	else
		this->going_to_run_ = false;
	//[DEBUG]stats = std::to_string(this->group_id_);
	//[DEBUG]stats.append(" ma ");
	//[DEBUG]stats.append(std::to_string(this->number_of_clients_));
	//[DEBUG]stats.append(" klientow. Tworze ja w czasie symulacji: ");
	//[DEBUG]stats.append( std::to_string(this->my_restaurant_->GetClock()));
	//[DEBUG]stats.append(" Grupa idzie do: ");
	//[DEBUG]if (to_tables_) {
	//[DEBUG]	stats.append("stolikow. ");
	//[DEBUG]}
	//[DEBUG]else 
	//[DEBUG]	stats.append("bufetu. ");
}

int Group::GroupId() 
{
	return group_id_;
}

int Group::NumberOfClients() 
{
	return number_of_clients_;
}

bool Group::BevragesServed() 
{
	return bevrages_served_;
}

bool Group::MainDishServed() 
{
	return main_dish_served_;
}

int Group::GetWaitingTime() 
{
	return waiting_time_;
}

void Group::SetMainDishServed(bool maindish)
{
	this->main_dish_served_ = maindish;
}

void Group::SetBevragesServed(bool beverages_served)
{
	this->bevrages_served_ = beverages_served;
}

void Group::SetWaitingTime(int time) {
	this->waiting_time_ = time;
}

bool Group::GetToTables()
{
	return this->to_tables_;
}

bool Group::GetBeingServed()
{
	return being_served_;
}

void Group::SetBeingServed(bool a)
{
	this->being_served_ = a;
}

bool Group::GetAtQueue()
{
	return at_queue;
}

void Group::SetAtQueue(bool a)
{
	at_queue = a;
}

bool Group::GetAte()
{
	return ate_;
}

void Group::SetAte(bool a)
{
	this->ate_ = a;
}

int Group::index_ = 0;