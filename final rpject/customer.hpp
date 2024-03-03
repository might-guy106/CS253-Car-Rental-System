#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "common_functions.hpp"
#include "user.hpp"
using namespace std;

class customer : public user {

public:

	customer(string name, int id, string pswd);                               // customer constructor 

	void display_avail_cars(MYSQL* conn);                                     // display Unrented Cars for customer 

	void display_my_rentings(MYSQL* conn);                                    // display Cars rented by customer currently 

	void rent_request(MYSQL* conn);                                           // customer request to rent a car

	void return_request(MYSQL* conn);                                         // customer request to return a car

	void clear_due_request(MYSQL* conn);                                      // customer request to clear his total dues 

	void customer_functions(MYSQL* conn);                                     // to access above all functions

};


#endif // CUSTOMER_H