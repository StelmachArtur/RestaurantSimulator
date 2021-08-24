#pragma once

#include "GroupApperance.h"
class Restaurant;

class Group : public GroupApperance
{
public:
	
	explicit Group(Restaurant *my_restaurant,bool totables);
	void Execute(int clock);
	//getters / setters
	int GroupId();
	int NumberOfClients();
	bool BevragesServed();
	bool MainDishServed();
	int GetWaitingTime();
	void SetMainDishServed(bool maindish);
	void SetBevragesServed(bool beverages_served);
	void SetWaitingTime(int time);
	bool GetToTables();
	bool GetBeingServed();
	void SetBeingServed(bool);
	bool GetAtQueue();
	void SetAtQueue(bool);
	bool GetAte();
	void SetAte(bool);
	bool GetGoingToRun();

	//[DEBUG]	std::string stats;
private:
	static int index_;
	
	Restaurant *my_restaurant_;
	int group_id_;	//id of group
	int number_of_clients_; //number of clients in a group
	bool to_tables_;	//true if group is going to tables
	bool at_queue;	//true if group is at queue
	bool going_to_run_;	//true if group is going to run at first alaram
	bool ate_;	// true if group already eaten
	bool being_served_;		//true if group is being served
	bool bevrages_served_;	//boolean if the vevrages were served
	bool main_dish_served_;  // boolean if whole group has been served
	int waiting_time_;  //variable for time of simulation when a group joined a queue then for time of simulation when group sat at table and at last for TOS when group joined to cashpoint queue
};
