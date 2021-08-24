#include "Restaurant.h"




RestaurantManager::RestaurantManager(const int service_time) :kServiceTime_(service_time)
{
	this->current_ = nullptr;
	this->busy_ = false;
}

void RestaurantManager::SetMyRestaurant(Restaurant* restaurant) {
	this->my_restaurant_ = restaurant;
}

int RestaurantManager::ServiceTime() const
{
	return kServiceTime_;
}

Group* RestaurantManager::Current() const
{
	return current_;
}

void RestaurantManager::SetActivationTime(int clock) {
	/**/if (my_restaurant_->GetMode() != 3)
	std::cout << "Setting execute_time of manager to: " << clock << std::endl;
	this->execute_time_ = clock;
}

void RestaurantManager::SetBusy(bool busy)
{
	/**/if (my_restaurant_->GetMode() != 3)
	std::cout << "Setting restaurant menager busy=true sim time: " << my_restaurant_->GetClock() << std::endl;
	
	this->busy_ = true;
}

std::pair<Table*, Group*> RestaurantManager::GetGroupToSeat()
{
	std::pair<Table*, Group*> temppair(nullptr, nullptr);
	std::vector<std::pair<Table*, Group*>> temp(4,temppair);

	my_restaurant_->GetSeatTable(&temp);
	my_restaurant_->GetSeatGroup(&temp);

	if (temp[3].first != nullptr && temp[3].second != nullptr) {
		return temp[3];
	}
	else if (temp[2].second != nullptr && (temp[2].first != nullptr || temp[3].first != nullptr)) {
		if (temp[2].first != nullptr) {
			return temp[2];
		}
		else {
			temp[2].first = temp[3].first;
			return temp[2];
		}
	}
	else if (temp[1].second != nullptr && (temp[1].first !=nullptr || temp[2].first != nullptr || temp[3].first != nullptr)) {
		if (temp[1].first != nullptr) {
			return temp[1];
		}
		else if (temp[2].first != nullptr) {
			temp[1].first = temp[2].first;
			return temp[1];
		}
		else {
			temp[1].first = temp[3].first;
			return temp[1];
		}
	}
	else if (temp[0].second != nullptr && (temp[1].first != nullptr || temp[2].first != nullptr || temp[3].first != nullptr)) {
		if (temp[1].first != nullptr) {
			temp[0].first = temp[1].first;
			return temp[0];
		}
		else if (temp[2].first != nullptr) {
			temp[0].first = temp[2].first;
			return temp[0];
		}
		else {
			temp[0].first = temp[3].first;
			return temp[0];
		}
	}
	return temppair;
}


void RestaurantManager::Execute(int clock)
{
	/**/if (my_restaurant_->GetMode() != 3)
	std::cout << "Execute of manager sim time:" << my_restaurant_->GetClock() << std::endl;
	this->busy_ = false;
	
}

bool RestaurantManager::Busy()
{
	return this->busy_;
}
