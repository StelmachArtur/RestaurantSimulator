#include "Restaurant.h"


int main()
{
	std::default_random_engine generator;
	RestaurantManager restaurant_manager(35);
	Restaurant restaurant(11, 5, 12, 6, 5,generator, restaurant_manager,18);
	restaurant_manager.SetMyRestaurant(&restaurant);
	Event *current = nullptr;
	bool event_trig = false;
	restaurant.AddEventToList(new GroupApperance(&restaurant, restaurant.normalDist(180,50))); 
	restaurant.AddEventToList(new Alarm(&restaurant));

	std::cout << "Pick simulation type:\n1 - continous\n2 - step by step\n";
	std::cout << "3 - Quick - (no debug)\n";
	int mode;
	std::cin >> mode;
	restaurant.SetMode(mode);

	int seed;
	do {
		std::cout << "Pick a seed (1-10):\n";
		std::cin >> seed;
	} while (seed <= 0 or seed > 10);
	restaurant.SetSeed(seed);

	while (restaurant.GetGroupsServed() <= 5000) { // To avoid dividing random number by random number we need to specify known value when simulation ends. 
		if (restaurant.GetMode() == 2)
			getchar();
		if (restaurant.event_list_.size() != 0) {
			current = *(restaurant.event_list_.begin()); // Pointer to closest event. This list is always sorted by execution time. 

			if (restaurant.GetClock() >= 8000) { // Around this simulation time simulator is in stable state.
				restaurant.SetTableAvrLength((current->execute_time_ - restaurant.GetClock())*restaurant.GetTableQueue().size()); // Update avr queue to table length
				restaurant.SetCashierAvrLength((current->execute_time_ - restaurant.GetClock())*restaurant.GetCashierQueue().size()); // Update avr queue cashier length
			}
			restaurant.SetClock(current->execute_time_); // Update simulation clock
			current->Execute(restaurant.GetClock()); // Execute specific object event 
			restaurant.event_list_.pop_front(); 
			if (typeid(current) == typeid(GroupApperance)) {
				if (restaurant.GetMode()!=3)
					std::cout << "Usuwam GroupApperance z pamieci. \n";
				delete current;
			}
			do {
				event_trig = false;
				if (!restaurant_manager.Busy() and restaurant.GetTableQueue().size() != 0) {
					auto table_group = restaurant_manager.GetGroupToSeat(); // Search for Group that wants and can find a Table
					if (table_group.first != nullptr) {
						restaurant_manager.SetBusy(true); //manager is starting serving a group
						if (restaurant.GetClock() >= 8000)
							restaurant.SetTableQueueWaitTime(restaurant.GetClock() - table_group.second->GetWaitingTime()); //adding waiting time for table of that group

						restaurant_manager.execute_time_ = restaurant.GetClock() + restaurant_manager.ServiceTime(); //setting managers next activation time
						restaurant.AddEventToList(&restaurant_manager); //putting manager back to event list

						table_group.first->SetCurrentGroup(table_group.second); //setting a pointer to a group in table object
						restaurant.RemoveGroupFromTableQueue(table_group.second); //removing a group from table queue

						//[DEBUG]if (restaurant.GetClock() >= 8000) {
						//[DEBUG]	restaurant.tables_queue_lengths_ << restaurant.GetTableQueue().size() << "\n";
						//[DEBUG]	restaurant.tables_queue_time_ << restaurant.GetClock() << "\n";
						//[DEBUG]}
						event_trig = true;
					}
				}
				if (restaurant.GetBuffetQueue().size() != 0 && restaurant.GetBuffetQueue().front()->NumberOfClients() <= restaurant.GetBuffet()->GetSpots()) {
					restaurant.GetBuffet()->PushToBuffetList(*restaurant.GetBuffetQueue().begin()); //adding first group in queue to buffet vector
					restaurant.GetBuffet()->SetSpots((*restaurant.GetBuffetQueue().begin())->NumberOfClients()); //removing spots in buffet
					(*restaurant.GetBuffetQueue().begin())->SetAtQueue(false);
					restaurant.RemoveGroupFromBuffetQueue(); // removing group from queue
					//[DEBUG]if (restaurant.GetClock() >= 8000) {
					//[DEBUG]	restaurant.buffet_queue_lengths_ << restaurant.GetBuffetQueue().size() << "\n";
					//[DEBUG]	restaurant.buffet_queue_time_ << restaurant.GetClock() << "\n";
					//[DEBUG]}
					event_trig = true;
				}
				if (restaurant.GetWaiter() != nullptr && restaurant.GetLongestWaitingGroup() != nullptr) {
					restaurant.GetWaiter()->SetWaiterCurrent(restaurant.GetLongestWaitingGroup());
					event_trig = true;

				}
				if (restaurant.GetCashier() != nullptr && restaurant.GetCashierQueue().size() != 0) {
					restaurant.GetCashier()->SetCashierCurrent(*restaurant.GetCashierQueue().begin());
					event_trig = true;

				}
			} while (event_trig);
		}
		if (restaurant.GetMode() != 3)
			std::cout << "--------------------------------------------------\nITERATION ENDS\n--------------------------------------------------\n";
	}
	restaurant.CalculateResults();
	
	std::cout << "SIMULATION ENDS!\n";
	
	//[DEBUG]restaurant.groups_data_.close();
	//[DEBUG]restaurant.waiters_data_.close();
	//[DEBUG]restaurant.cashiers_data_.close();
	//[DEBUG]restaurant.buffet_queue_lengths_.close();
	//[DEBUG]restaurant.cashier_queue_lengths_.close();
	//[DEBUG]restaurant.tables_queue_lengths_.close();
	//[DEBUG]restaurant.buffet_queue_time_.close();
	//[DEBUG]restaurant.cashier_queue_time_.close();
	//[DEBUG]restaurant.tables_queue_time_.close();
	
	std::cin.ignore();
	getchar();
	return 0;
}
