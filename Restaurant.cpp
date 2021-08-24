#include "Restaurant.h"





Restaurant::Restaurant(const int waiter_amount, const int t2, const int t3, const int t4, const int cashier_amount, std::default_random_engine generator,
                       RestaurantManager restaurant_manager,int buffet_capacity) : kWaiterAmount_(waiter_amount),
															   kTwoSeatTablesAmount_(t2),
                                                               kThreeSeatTablesAmount_(t3),
                                                               kFourSeatTablesAmount_(t4),
                                                               kCashierAmount_(cashier_amount),
                                                               restaurant_manager_(restaurant_manager),clock_(0),generator(generator),buffet(Buffet(buffet_capacity,this))
{
//1 4862.03 12.3541 14.1058 4248.17
//2 5820.11 15.1483 14.5249 4453.65
//3	6118.6 16.7442 10.3577 4335.56
//4 9242.09 26.0134 7.20659
//5 5750.71 15.5961 12.5277 4400.81
//6 12653.5 36.8452 13.074 4957.67
//7 5186.91 13.0138 9.80391 4565.8 
//8 3654.99 10.2999 10.7964 4084.98
//9 5520.64 19.8038 12.1647 4430.73
//10 15123.1 45.7399 17.7248 4774.3

	groups_served_ = 0;


	//[DEBUG]groups_data_.open("groupData10.txt",std::ios::out);
	//[DEBUG]waiters_data_.open("waitersData10.txt", std::ios::out);
	//[DEBUG]cashiers_data_.open("cashiersData10.txt", std::ios::out);
	
	//[DEBUG]buffet_queue_lengths_.open("buffQLeng10.txt", std::ios::out);
	//[DEBUG]cashier_queue_lengths_.open("cashQLen10.txt", std::ios::out);
	//[DEBUG]tables_queue_lengths_.open("tabQLen10.txt", std::ios::out);

	//[DEBUG]buffet_queue_time_.open("buffQTime10.txt", std::ios::out);
	//[DEBUG]cashier_queue_time_.open("cashQTime10.txt", std::ios::out);
	//[DEBUG]tables_queue_time_.open("tabQtime10.txt", std::ios::out);

	//[DEBUG]system_groups_amount_.open("systemamount10.txt", std::ios::out);
	//[DEBUG]system_groups_times_.open("systemtimes10.txt", std::ios::out);
	table_queue_wait_time_ =0;
	table_queue_amount_=0;

	table_avr_length_=0;
	cashier_avr_length_=0;

	tables_waiting_times_=0;
	tables_waiting_times_amount_=0;

	groups_served_ = 0;
	std::list<Group*> table_queue_;
	std::list<Group*>  cashier_queue_;
	std::list<Group*>  buffet_queue_;
	this->waiters_ = std::vector<Waiter>();
	std::list<Event*> event_list_;
	for (int i = 0; i < kWaiterAmount_; i++) {
		this->waiters_.push_back(Waiter(this));
	}
	this->cashiers_ = std::vector<Cashier>();
	for (int i = 0; i < t2; i++)
	{
		this->cashiers_.push_back(Cashier(this));
	}
	this->tables_ = std::vector<Table>();
	for (int i = 0; i < t2; i++)
	{
		this->tables_.push_back(Table(2, this));
	}
	for (int i = 0; i < t3; i++)
	{
		this->tables_.push_back(Table(3,this));
	}
	for (int i = 0; i < t4; i++)
	{
		this->tables_.push_back(Table(4,this));
	}


	
}


void Restaurant::SetTableQueue(std::list<Group*> temp) {
	this->table_queue_ = temp;

}
void Restaurant::RemoveGroupFromBuffetQueue()
{
	buffet_queue_.pop_front();

}
void Restaurant::RemoveGroupFromCashierQueue()
{
	this->cashier_queue_.pop_front();
}

void Restaurant::RemoveGroupFromBuffetQueue(Group* a)
{
	buffet_queue_.remove(a);

}
void Restaurant::RemoveGroupFromCashierQueue(Group* a)
{
	this->cashier_queue_.remove(a);
}

void Restaurant::RemoveGroupFromCashier(Group* a)
{
	for (auto itr = this->cashiers_.begin(); itr != this->cashiers_.end(); itr++) {
		if ((*itr).GetCurrent() == a) {
			(*itr).SetCashierCurrent(nullptr);
			this->RemoveCashierFromEventList(&*itr);
		}
	}
}


std::list<Group>::iterator Restaurant::RemoveGroupFromRestaurant(Group * grp)
{
	IncrGroupsServed();
		for (auto itr = groups_.begin(); itr != groups_.end(); itr++) {
			if (&(*itr) == grp) {
				/**/	if (mode_ != 3)
				std::cout << "Delete group id: " << grp->GroupId() << " from restaurant\n";
				//[DEBUG]grp->stats.append(" Grupa zostaje usunieta w czasie symulacji: ");
				//[DEBUG]grp->stats.append(std::to_string(this->GetClock()));
			
				//[DEBUG]std::cout << grp->stats<<std::endl;
				//[DEBUG]groups_data_ << (grp->stats) << std::endl;
				//[DEBUG]this->system_groups_amount_ << this->groups_.size()-1 << "\n";
				//[DEBUG]this->system_groups_times_ << this->GetClock() << "\n";
				return groups_.erase(itr);
				
			}
		}
		return std::list<Group>::iterator();
}
Waiter * Restaurant::GetWaiter()
{
	for (auto itr = waiters_.begin(); itr != waiters_.end(); itr++) {
		if ((*itr).GetWaiterCurrent() == nullptr) {
			return &(*itr);
		}
	}
	return nullptr;
}
void Restaurant::SetClock(int newTime) {
	this->clock_ = newTime;
}

void Restaurant::RemoveGroupFromTableQueue(Group * a) {
	this->table_queue_.remove(a);
	a->SetAtQueue(false);
}

void Restaurant::PushTableGroup(Group* new_group)
{
	this->table_queue_.push_back(new_group);
}

void Restaurant::displayQueue(std::list<Group*> a) {
	for (auto itr = a.begin(); itr != a.end(); itr++) {
		/**/if (mode_ != 3)
		std::cout <<"Group index "<< (*itr)->GroupId() <<" has " <<(*itr)->NumberOfClients() << std::endl;
	}
	
}

void Restaurant::SetTableQueueWaitTime(int new_wait_time)
{
	if(this->clock_ >= 8000)
	this->table_queue_wait_time_ += new_wait_time;
	/**/if (mode_ != 3)
		std::cout << "Next waiting time to the table has been added: " << new_wait_time << "\n";
	IncrTableQueueAmount(); // incrementing amount of group taken into count
}

void Restaurant::SetTablesWaitingTimes(int a)
{
	if (this->clock_ >= 8000) {
		this->tables_waiting_times_ += a;
		IncrTablesWaitingTimesAmount();
	}
}

void Restaurant::IncrTablesWaitingTimesAmount()
{
	if(this->clock_ >=8000)
		this->tables_waiting_times_amount_++;
}

void Restaurant::SetTableAvrLength(int time)
{
	if (this->clock_>=8000)
		table_avr_length_ += time;
}

void Restaurant::CalculateResults() {
	std::cout << "Simulation results: \n";
	std::cout << "Cummulative waiting time of all groups: " << table_queue_wait_time_ << "\t Number of groups: " << table_queue_amount_ << " Average wait time in queue to table:" << table_queue_wait_time_ / (double)table_queue_amount_<<"\n";
	std::cout << "Average length of queue to tables: " << table_avr_length_ / (double)clock_<<"\n";
	std::cout << "Average length of queue to cashiers:: " << cashier_avr_length_ / (double)clock_ << "\n";
	std::cout << "Average service time at a table: " << tables_waiting_times_ / (tables_waiting_times_amount_/2.0) << "\n";

	
}

void Restaurant::SetCashierAvrLength(unsigned int time)
{
	if (this->clock_>=8000)
	cashier_avr_length_ += time;
}

void Restaurant::IncrTableQueueAmount()

{
	if (this->clock_>=8000)
	this->table_queue_amount_++;
}

Buffet * Restaurant::GetBuffet()
{
	return &buffet;
}

void Restaurant::PushCashierGroup(Group* new_group)
{
	/**/if (mode_ != 3)
	std::cout << "Adding group id "<<new_group->GroupId()<<" to the queue to cashiers.\n";
	this->cashier_queue_.push_back(new_group);
}

void Restaurant::PushBuffetGroup(Group* new_group)
{
	this->buffet_queue_.push_back(new_group);
}

void Restaurant::GetSeatTable(std::vector<std::pair<Table*,Group*>>* a)
{
	for (auto itr = tables_.begin(); itr != tables_.end(); itr++) {
		if (itr->GetCurrentGroup() == nullptr && itr->GetAmountOfSits()!=1) {
			switch (itr->GetAmountOfSits()) {
				case 2: {
					if ((*a)[1].first == nullptr) {
						(*a)[1].first = &(*itr);
					}
					break;
				}
				case 3: {
					if ((*a)[2].first == nullptr) {
						(*a)[2].first = &(*itr);
					}
					break;
				}
				case 4: {

					if ((*a)[3].first == nullptr) {
						(*a)[3].first = &(*itr);
					}				
				}
			}
		}
	}
}

void Restaurant::GetSeatGroup(std::vector<std::pair<Table*, Group*>>* a)
{
	for (auto itr = table_queue_.begin(); itr != table_queue_.end(); itr++) {
		int clients = (*itr)->NumberOfClients();
		if ((*a)[clients - 1].second == nullptr) {
			(*a)[clients - 1].second = (*itr);
		}
	}
}


std::vector<Waiter> Restaurant::GetWaiters()
{
	return waiters_;
}

std::vector<Table> Restaurant::GetTables()
{
	return tables_;
}

std::vector<Cashier> Restaurant::GetCashiers()
{
	return cashiers_;
}

std::list<Group> Restaurant::GetGroups()
{
	return groups_;
}

int Restaurant::GetClock () {
	return clock_;
}

void Restaurant::RemoveGroupFromTables(Group * grp)
{
	for (auto itr = tables_.begin(); itr != tables_.end(); itr++) {
		if ((*itr).GetCurrentGroup() == grp) {
			(*itr).SetCurrentGroup(nullptr);
		}
	}
}

Group* Restaurant::GetLongestWaitingGroup()
{
	int diff = 0;
	Group* grp = nullptr;
	for (auto itr = tables_.begin(); itr != tables_.end(); itr++) {
		if ((*itr).GetCurrentGroup() != nullptr && (*itr).GetCurrentGroup()->MainDishServed() != true && !(*itr).GetCurrentGroup()->GetBeingServed()) {
			int temp;
			temp = clock_ - (*itr).GetCurrentGroup()->execute_time_;
			if (temp > diff) {
				diff = temp;
				grp = (*itr).GetCurrentGroup();
			}
		}
	}
	return grp;
}

int Restaurant::normalDist(double mean, double stddev)
{
	std::normal_distribution<double> normal(mean, stddev);
	double number = normal(this->generator);
	return (int)number;
}

int Restaurant::expDist(double lambda)
{
	std::exponential_distribution<double> exp(lambda);
	double number = exp(this->generator);
	return (int)number;
}

RestaurantManager Restaurant::GetRestaurantManager()
{
	return restaurant_manager_;
}

int Restaurant::GetWaiterAmount()
{
	return kWaiterAmount_;
}

int Restaurant::GetTwoSeatTablesAmount()
{
	return kTwoSeatTablesAmount_;
}

int Restaurant::GetThreeSeatTablesAmount()
{
	return kThreeSeatTablesAmount_;
}

int Restaurant::GetFourSeatTablesAmount()
{
	return kFourSeatTablesAmount_;
}

int Restaurant::GetCashierAmount()
{
	return kCashierAmount_;
}

Cashier * Restaurant::GetCashier()
{
	for (auto itr = cashiers_.begin(); itr != cashiers_.end(); itr++) {
		if ((*itr).GetCurrent() == nullptr) return (&*itr);
	}
	return nullptr;
}

std::list<Group*> Restaurant::GetTableQueue()
{
	return table_queue_;
}

std::list<Event*> Restaurant::GetEventList() {
	return event_list_;
}

std::list<Group*> Restaurant::GetCashierQueue()
{
	return cashier_queue_;
}


std::list<Group*> Restaurant::GetBuffetQueue()
{
	return buffet_queue_;
}

void Restaurant::RemoveGroupFromEventList(Group* a) {
	auto b = dynamic_cast<Event*> (a); //so we can compare both pointers
	for (auto itr = event_list_.begin(); itr != event_list_.end();) {
		if ((*itr) == b) {

			itr = event_list_.erase(itr);


		}
		else {
			itr++;
		}
	}
}

int Restaurant::GetGroupsServed() {
	return groups_served_;
}

void Restaurant::IncrGroupsServed() {
	groups_served_ += 1;

}
void Restaurant::SetSeed(int seed)
{
	int myseeds[10] = { 495167,
		854506,
		456013,
		377423,
		993373,
		21464,
		270902,
		714627,
		190065,
		216049 };

	this->generator = std::default_random_engine(myseeds[seed-1]);
}

void Restaurant::RemoveCashierFromEventList(Cashier* a) {
	auto b = dynamic_cast<Event*> (a); //so we can compare both pointers
	for (auto itr = event_list_.begin(); itr != event_list_.end();) {
		if ((*itr) == b) {
		
			itr = event_list_.erase(itr);


		}
		else {
			itr++;
		}
	}
}

void Restaurant::RemoveGroupFromWaiters(Group * a)
{
	for (auto itr = waiters_.begin(); itr != waiters_.end(); itr++) {
		if ((*itr).GetWaiterCurrent() == a) {
			(*itr).SetWaiterCurrent(nullptr);	//reseting pointer on group if its leaving
			this->RemoveWaitersFromEventList(&*itr);   //since we removed its pointer we got to remove him form event list
		}
	}
}

void Restaurant::RemoveWaitersFromEventList(Waiter * a)
{
	auto b = dynamic_cast<Event*> (a); //so we can compare both pointers
	for (auto itr = event_list_.begin(); itr != event_list_.end();) {
		if ((*itr) == b) {
			itr = event_list_.erase(itr);


		}
		else {
			itr++;
		}
	}
}


void Restaurant::AddEventToList(Event* a)
{
	int size = this->event_list_.size();
	if (size == 0) {
		this->event_list_.push_back(a);
	}
	else {
		for (std::list<Event*>::iterator iterator=event_list_.begin(); iterator!=event_list_.end();iterator++) {
			if ((*iterator)->execute_time_ > a->execute_time_) {
				event_list_.insert(iterator, a);
				return;
			}
		}
		event_list_.push_back(a);
	}
}

int Restaurant::GetMode()
{
	return mode_; 
}

void Restaurant::SetMode(int mod)
{
	this->mode_ = mod;
}

void Restaurant::PrintEventList() {
	/**/if (mode_ != 3)
	std::cout << "Event list:" << std::endl;
	for (std::list<Event*>::iterator iterator = event_list_.begin(); iterator != event_list_.end(); iterator++) {
		std::cout << (*iterator)->execute_time_ << std::endl;
	}
}

void Restaurant::PrintTableQueue() {
	/**/	if (mode_ != 3)
	std::cout << "Table queue:" << std::endl;
	for (std::list<Group*>::iterator iterator = this->table_queue_.begin(); iterator != this->table_queue_.end(); iterator++) {
		std::cout << "Group ID: "  <<(*iterator)->GroupId()<< " has "<< (*iterator)->NumberOfClients() << " clients" << std::endl;
	}
}