# RestaurantSimulator
Simulator of a restaurant

In this project we are trying to simulate a working restaurant using good simulation techniques. 

Restaurant works like this. 
1. At random time gorup of clients (1-4 people) appears in the restaurant. 

2. Group selects if they would like to eat at the table or take f!ood to go from the buffet.

3.a If the buffet is sellected

    4. Take seats in the buffet or if no seats stand in the queue
    
3.b If table is selected

    4.a Wait for RestaurantManager to lead a group to tables (if available)
    
    4.b When group is at a table wait for waiters to be serviced
    
    4.c Group eats
    
5. Groups from buffet or tables go to cashiers or wait in a queur

6. Group leaves

When simulation is done some statistics are provided.
