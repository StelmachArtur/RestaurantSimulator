#include "Restaurant.h"

Alarm::Alarm(Restaurant * res)
{
	this->my_restaurant_ = res;
	this->execute_time_=my_restaurant_->GetClock() + my_restaurant_->normalDist(3000, 50);
}

void Alarm::Execute(int clock)
{
	/**/if (my_restaurant_->GetMode() !=3)
	std::cout << "ATTENTION ALARM! \n";
	
	for (auto itr = my_restaurant_->groups_.begin(); itr != my_restaurant_->groups_.end();) {
		if ((*itr).GetGoingToRun()) {
			//[DEBUG]	(*itr).stats.append("ALARM WE ARE ESCAPING: simuation time ");
		//[DEBUG]	(*itr).stats.append(std::to_string(my_restaurant_->GetClock()));
			if ((*itr).GetAtQueue() && (*itr).GetAte()) {  //The group is at cashiers queue
			//[DEBUG]	(*itr).stats.append("CASHIERS QUEUE ");
			//[DEBUG]	(*itr).stats.append(std::to_string(my_restaurant_->GetClock()));
				my_restaurant_->RemoveGroupFromCashierQueue(&*itr); //since noone has pointer to that group we can simply remove it from cashier queue
				
			}
			else if ((*itr).GetAtQueue() && !(*itr).GetAte() && (*itr).GetToTables()) { // the group is at table quqeue
			//[DEBUG]	(*itr).stats.append("TABLE QUEUE ");
			//[DEBUG]	(*itr).stats.append(std::to_string(my_restaurant_->GetClock()));
				my_restaurant_->RemoveGroupFromTableQueue(&*itr); //since noone has pointer to that group we can just remove it from table queue
				
			}

			else if ((*itr).GetAtQueue() && !(*itr).GetAte() && !(*itr).GetToTables()) { //group is in buffet queue
			//[DEBUG]	(*itr).stats.append("BUFFET QUEUE ");
			//[DEBUG]	(*itr).stats.append(std::to_string(my_restaurant_->GetClock())); 
			    my_restaurant_->RemoveGroupFromBuffetQueue(&*itr); //since noone has pointer to that group we can just remove it from buff queue
			
			}
			else if (!(*itr).GetAtQueue() && !(*itr).GetAte() && !(*itr).GetToTables()) { //group is in the buffet
			//[DEBUG]	(*itr).stats.append(" BUFFET ");
			//[DEBUG]	(*itr).stats.append(std::to_string(my_restaurant_->GetClock()));
				my_restaurant_->GetBuffet()->RemoveFromBuffet(&*itr);  //removing group from buffet.
				my_restaurant_->RemoveGroupFromEventList(&*itr); //since we planned finish of eating we need to remove it from event list
				
			}
			else if (!(*itr).GetAtQueue() && !(*itr).GetAte() && (*itr).GetToTables()) { //group is at tables
			//[DEBUG]	(*itr).stats.append(" TABLES ");
			//[DEBUG]	(*itr).stats.append(std::to_string(my_restaurant_->GetClock()));
				my_restaurant_->RemoveGroupFromTables(&(*itr));		//removing group from their table so other groups can take it
				if ((*itr).MainDishServed()) // if maindish is true we planned group finish of eat time and we need to remove it
				my_restaurant_->RemoveGroupFromEventList(&*itr); 
				if (!(itr->MainDishServed())) //it means someone is giving food / drinks to that group and we need to take care of it
				my_restaurant_->RemoveGroupFromWaiters(&*itr);
			
			}
			else if (!(*itr).GetAtQueue() && (*itr).GetAte()) { //group is at cashier
			//[DEBUG]	(*itr).stats.append(" CASHIERS ");
			//[DEBUG]	(*itr).stats.append(std::to_string(my_restaurant_->GetClock()));
				my_restaurant_->RemoveGroupFromCashier(&*itr); // if they are at cashiers just set cashiers pointer to nullptr			
			}
			itr = my_restaurant_->RemoveGroupFromRestaurant(&*itr); //removing that group from restaurant.
			}
		else {
			itr++;
		}
	}
	this->execute_time_ = my_restaurant_->GetClock() + my_restaurant_->normalDist(3000, 50);
	this->my_restaurant_->AddEventToList(this);
}
