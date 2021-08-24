#include "Restaurant.h"

Buffet::Buffet(const int buffet_capacity,Restaurant * res): kBuffetCapacity_(buffet_capacity)
{
	this->my_restaurant_ = res;
	this->current_ = std::list<Group*>();
	this->spots_ = buffet_capacity;

}

void Buffet::SetSpots(int seats)
{
	
	spots_ -= seats;
	/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Decreasing seats at the buffet " << seats << " left: " << this->spots_ <<"." <<std::endl;
}

int Buffet::GetSpots()
{
	return spots_;
}

void Buffet::PushToBuffetList(Group * grp)
{
	/**/	if (my_restaurant_->GetMode() != 3)
		std::cout << "Group index: "<<grp->GroupId()<<" seats in the buffet." << std::endl;
	current_.push_back(grp);
	grp->execute_time_ = my_restaurant_->GetClock() + my_restaurant_->normalDist(3200, 100); //todo
	/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Group will leave the buffet at smulation time: " << grp->execute_time_ << "\n";
	my_restaurant_->AddEventToList(grp);
}

void Buffet::RemoveFromBuffet(Group * grp)
{
	/**/if (my_restaurant_->GetMode() != 3)
		std::cout << "Removing group index: " << grp->GroupId() << " from buffet. In simulation time "<<my_restaurant_->GetClock()<<"\n" ;
	this->SetSpots(-grp->NumberOfClients());
	current_.remove(grp);
}

