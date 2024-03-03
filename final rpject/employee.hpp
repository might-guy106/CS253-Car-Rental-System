#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "common_functions.hpp"
#include "user.hpp"
using namespace std;

class employee : public user {

public:

	employee(string name, int id, string pswd);                               // employee constructor

	void display_avail_cars(MYSQL* conn);                                     // display Unrented Cars for employee

	void display_my_rentings(MYSQL* conn);                                    // display Cars rented by employee currently

	void rent_request(MYSQL* conn);                                           // employee request to rent a car

	void return_request(MYSQL* conn);                                         // employee request to return a car

	void clear_due_request(MYSQL* conn);                                      // employee request to clear his total dues 

	void employee_functions(MYSQL* conn);                                     // to access above all functions

};


#endif // EMPLOYEE_H