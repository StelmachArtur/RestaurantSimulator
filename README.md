# RestaurantSimulator
Simulator of a restaurant

In this project we are trying to simulate a working restaurant using good simulation techniques. 

Restaurant works like this. 
1. At random time gorup of clients (1-4 people) appears in the restaurant. 
2. Group selects if they would like to eat at the table or take food to go from the buffet.
2.a If the buffet is sellected
    3. Take seats in the buffet or if no seats stand in the queue
2.b If table is selected 
    3.a Wait for RestaurantManager to lead a group to tables (if available)
    3.b When group is at a table wait for waiters to be serviced
    3.c Group eats
4. Groups from buffet or tables go to cashiers or wait in a queue
5. Group leaves

When simulation is done some statistics are provided.
