#pragma once
#include "RestaurantManager.h"


class Restaurant
{
public:
	
	Restaurant(const int waiter_amount, const int t2, const int t3, const int t4, const int cashier_amount, std::default_random_engine generator, RestaurantManager restaurant_manager,int buffet_capacity);
	~Restaurant() = default;
	std::default_random_engine generator;
	//Pliki wyjsciowe
	//[DEBUG]std::fstream groups_data_;
	//[DEBUG]std::fstream waiters_data_;
	//[DEBUG]std::fstream cashiers_data_;
	//[DEBUG]std::fstream buffet_queue_lengths_;
	//[DEBUG]std::fstream cashier_queue_lengths_;
	//[DEBUG]std::fstream tables_queue_lengths_;
	//[DEBUG]std::fstream buffet_queue_time_;
	//[DEBUG]std::fstream cashier_queue_time_;
	//[DEBUG]std::fstream tables_queue_time_;
	//[DEBUG]std::fstream system_groups_amount_;
	//[DEBUG]std::fstream system_groups_times_;
	//getters / setters
	std::vector<Waiter> GetWaiters() ;
	std::vector<Table> GetTables() ;
	std::vector<Cashier> GetCashiers() ;
	std::list<Group> GetGroups();
	RestaurantManager GetRestaurantManager() ;
	int GetWaiterAmount() ;
	int GetTwoSeatTablesAmount() ;
	int GetThreeSeatTablesAmount();
	int GetFourSeatTablesAmount() ;
	int GetCashierAmount() ;
	Cashier* GetCashier();
	int GetClock();
	int GetGroupsServed();
	void SetSeed(int seed);
	void SetClock(int newTime);
	std::list<Group*> GetTableQueue();
	std::list<Group*> GetCashierQueue();
	std::list<Group*> GetBuffetQueue();
	std::list<Event*> GetEventList();
	void GetSeatTable(std::vector<std::pair<Table*, Group*>>* a);
	void GetSeatGroup(std::vector<std::pair<Table*, Group*>>* a);
	int GetMode();
	void SetMode(int);
	void SetTableQueueWaitTime(int);
	void SetTablesWaitingTimes(int);
	void IncrTablesWaitingTimesAmount();
	void SetTableAvrLength(int);
	void SetCashierAvrLength(unsigned int);
	void IncrTableQueueAmount();
	void IncrGroupsServed();
	Buffet* GetBuffet();
	Group* GetLongestWaitingGroup();
	void SetTableQueue(std::list<Group*> temp);


	int expDist(double lambda);
	int normalDist(double mean, double stddev);
	void RemoveGroupFromTables(Group* grp);
	void RemoveGroupFromBuffetQueue();
	void RemoveGroupFromCashierQueue();
	void RemoveGroupFromBuffetQueue(Group * a);
	void RemoveGroupFromCashierQueue(Group * a);
	void RemoveGroupFromTableQueue(Group * a);
	void RemoveGroupFromCashier(Group * a);
	void RemoveGroupFromEventList(Group* a);
	void RemoveCashierFromEventList(Cashier * a);
	void RemoveGroupFromWaiters(Group* a);
	void RemoveWaitersFromEventList(Waiter * a);
	std::list<Group>::iterator RemoveGroupFromRestaurant(Group * grp);
	Waiter* GetWaiter();
	std::list<Group> groups_;	// vector of group
	void PushTableGroup(Group* new_group);
	void PushCashierGroup(Group* new_group);
	void PushBuffetGroup(Group* new_group);
	void PrintEventList();
	void PrintTableQueue();
	void AddEventToList(Event* a);
	void displayQueue(std::list<Group*> a);
	std::list<Event*> event_list_;
	void CalculateResults();
	
private:
	const int kWaiterAmount_;	// amount of waiters
	const int kTwoSeatTablesAmount_;	//amount of 2 seat tables
	const int kThreeSeatTablesAmount_;	//amount of 3 seat tables
	const int kFourSeatTablesAmount_;	 // amount of 4 seat tables
	const int kCashierAmount_;	// amount of cashiers

	int groups_served_; //amount of groups served in simulation
	int clock_; //simulation time
	int mode_; //mode of simulation (stepped, continous, quick)
	int table_queue_wait_time_;		
	int table_queue_amount_; 
	long table_avr_length_;
	long cashier_avr_length_;
	int tables_waiting_times_;
	int tables_waiting_times_amount_;
	Buffet buffet;
	RestaurantManager restaurant_manager_; // instance of restaurant menager
	std::vector<Waiter> waiters_;	//vector of waiters
	std::vector<Table> tables_;	//vector of all tables
	std::vector<Cashier>cashiers_;	// vector of cashiers
	std::list<Group*> table_queue_;		//  queue to tables
	std::list<Group*>  cashier_queue_;	//	queue to cashiers
	std::list<Group*>  buffet_queue_;	// queue to buffet
};
