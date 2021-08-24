#include "Restaurant.h"





Group* Waiter::GetWaiterCurrent()
{
	return this->current_;
}

void Waiter::SetWaiterCurrent(Group* grp)
{
	if (grp != nullptr) {
		/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Setting waiter to a group. Simulation time:" << my_restaurant_->GetClock() << " id is: " << this->id_ << "\n";
		this->current_ = grp;
		//[DEBUG]grp->stats.append(" Grupa otrzymuje kelnera w czasie symulacji: ");
		//[DEBUG]grp->stats.append(std::to_string(my_restaurant_->GetClock()));
		//[DEBUG]this->stats.append(" kelner otrzymuje grupe w czasie symulacji: ");
		//[DEBUG]this->stats.append(std::to_string(my_restaurant_->GetClock()));
		//[DEBUG]this->stats.append(" Id grupy: ");
		my_restaurant_->SetTablesWaitingTimes(my_restaurant_->GetClock() - current_->GetWaitingTime());
		//[DEBUG]this->stats.append(std::to_string(current_->GroupId()));
		grp->SetWaitingTime(my_restaurant_->GetClock()); //ustawienie czasu ostatniego obsluzenia na aktualny czas symulacji.
		if (current_->BevragesServed()) { // jezeli bevereges served jest true to oznacza ze podane dane glowne i mozna ustawic czas zjedzenia.


			current_->execute_time_ = my_restaurant_->GetClock() + my_restaurant_->expDist(1 / 4350.0);
			this->execute_time_ = current_->execute_time_;
			//[DEBUG]grp->stats.append(" Grupa powinna otrzymac jedzenie w czasie symulacji: ");
			//[DEBUG]grp->stats.append(std::to_string(current_->execute_time_));
		}
		else {

			current_->SetBeingServed(true);
			this->execute_time_ = my_restaurant_->expDist(1 / 1400.0) + my_restaurant_->GetClock();
			current_->execute_time_ = this->execute_time_;
			//[DEBUG]grp->stats.append(" Grupa powinna otrzymac picie w czasie symulacji: ");
			//[DEBUG]grp->stats.append(std::to_string(current_->execute_time_));
		}
		/**/	if (my_restaurant_->GetMode() != 3)
		std::cout << "resseting waiter Id: " << this->id_ << " sim time: " << this->execute_time_ <<  "\n";
		//[DEBUG]this->stats.append("Kelner powinien zostac zresetowany w czasie symulacji: ");
		//[DEBUG]this->stats.append(std::to_string(this->execute_time_));
		my_restaurant_->AddEventToList(this);
	}
	else {
		this->current_ = nullptr;
	}
}

Waiter::Waiter(Restaurant* res)
{
	
	std::cout << "Creating waiter id: " << ++index_ << "\n";
	this->id_ = index_;
	//[DEBUG]stats = std::to_string(this->id_);

	
	this->my_restaurant_ = res;
	this->current_ = nullptr;

}
void Waiter::Execute(int clock)
{
	/**/if (my_restaurant_->GetMode() != 3)
	std::cout << "Waiter execute. Setting pointer to nullptr. Group index: "<<this->id_<<" sim time: "<<my_restaurant_->GetClock()<<"\n";
	if (this->current_->BevragesServed()) {
		this->current_->SetMainDishServed(true);
		/**/	if (my_restaurant_->GetMode() != 3)
		std::cout << "Group recieves food: " << current_->GroupId() << "\n";
		current_->execute_time_ = my_restaurant_->GetClock() + my_restaurant_->expDist(1 / 2400.0);
		//[DEBUG]current_->stats.append(" Grupa otrzymuje jedzenie w czasie symulacji: ");
		//[DEBUG]current_->stats.append(std::to_string(my_restaurant_->GetClock()));
		/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Group will finish eating = " << current_->execute_time_ << "\n";
		my_restaurant_->AddEventToList(current_);
		//[DEBUG]current_->stats.append(" Grupa powinna skonczyc jesc w czasie symulacji: ");
		//[DEBUG]current_->stats.append(std::to_string(current_->execute_time_));
	}
	else {
		this->current_->SetBevragesServed(true);
		/**/	if (my_restaurant_->GetMode() != 3)
		std::cout << "Group got drinks: " << current_->GroupId() << "\n";
		current_->SetBeingServed(false);
		//[DEBUG]current_->stats.append(" Grupa otrzymuje picie w czasie symulacji: ");
		//[DEBUG]current_->stats.append(std::to_string(my_restaurant_->GetClock()));
	}

	//[DEBUG]this->stats.append("Zresetowany w czasie symulacji: ");
	//[DEBUG]this->stats.append(std::to_string(my_restaurant_->GetClock()));
	//[DEBUG]my_restaurant_->waiters_data_ << this->stats<<"\n";
	//[DEBUG]stats = std::to_string(this->id_);
	this->current_ = nullptr;

}

int Waiter::index_ = 0;