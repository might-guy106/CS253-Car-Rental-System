#ifndef MANAGER_H
#define MANAGER_H

#include "common_functions.hpp"
#include "user.hpp"
using namespace std;

class manager : public user {

public:

	manager(string name, int id, string pswd);

	void display_cars(MYSQL* conn);                                                    // Displays Cars Table
	void add_car(MYSQL* conn,int& CAR_ID, string& model, int& cond, int& price);       // add car to Cars table
	void delete_car(MYSQL* conn, int& car_id);                                         // delete car from Cars table
	void update_car(MYSQL*conn,int&car_id);

	void display_customers(MYSQL* conn);											   // Displays Customers Table
	void add_customer(MYSQL* conn, string& name, int& id, string& paswd);              // add customer to customer table
	void delete_customer(MYSQL* conn);                                                 // delete customer from customer table
	void update_customer(MYSQL* conn,int &customer_id);

	void display_employees(MYSQL* conn);                                                // Displays Employees Table
	void add_employee(MYSQL* conn, string& name, int& id, string& paswd);              // add employee to Employees table
	void delete_employee(MYSQL* conn);                                                 // delete employee from Employees table
	void update_employee(MYSQL* conn, int& customer_id);

	void modify_records(MYSQL* conn);                                                  // to access above all functions
	
};


#endif // MANAGER_H
