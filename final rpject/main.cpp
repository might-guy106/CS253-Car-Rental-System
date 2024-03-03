#include "customer.hpp"
#include "employee.hpp"
#include "manager.hpp"
using namespace std;


const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "123456";
const char* DB = "project";

const char* MANAGER_NAME = "manager_1";
const int MANAGER_ID = 1;
const char* MANAGER_PASWD = "man1";


void add_initial_data(MYSQL* conn) {

	// creating 5 cars

	string car_model;
	int car_id,car_price, car_cond;

	for (int i = 1; i <= 5; i++) {

		car_id = 1000 + i;
		car_model = "car_" + to_string(i);
		car_cond = i;
		car_price = i * 100;

		stringstream bs;
		bs << car_id;
		string temp_car_id = bs.str();

		stringstream ss;
		ss << car_cond;
		string temp_cond = ss.str();

		stringstream as;
		as << car_price;
		string temp_price = as.str();

		string ins = "INSERT INTO Cars (ID,Model,Cond,Price,Availability,Rented_By_ID,Dispatch_Date,Due_Date) VALUES ( " + temp_car_id + ",'" + car_model + "' , " + temp_cond + " , " + temp_price + " , DEFAULT ,DEFAULT,DEFAULT , DEFAULT )";
		if (mysql_query(conn, ins.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}

	}

	// creating 5 customers

	string customer_name, customer_paswd;
	int customer_id;

	for (int i = 1; i <= 5; i++) {

		customer_name = "customer_" + to_string(i);
		customer_id = 2000 + i;
		customer_paswd = "cus" + to_string(i);

		stringstream as;
		as << customer_id;
		string temp_customer_id = as.str();

		string ins = "INSERT INTO Customers (ID,Name,Password,Fine_Due,Score) VALUES ( " + temp_customer_id + ",'" + customer_name + "','" + customer_paswd + "',DEFAULT,3)";
		if (mysql_query(conn, ins.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}

	}

	// creating 5 employees

	string employee_name, employee_paswd;
	int employee_id;

	for (int i = 1; i <= 5; i++) {

		employee_name = "employee_" + to_string(i);
		employee_id = 3000 + i;
		employee_paswd = "emp" + to_string(i);

		stringstream ss;
		ss << employee_id;
		string temp_employee_id = ss.str();

		string ins = "INSERT INTO Employees (ID,Name,Password,Fine_Due,Score) VALUES ( " + temp_employee_id + ",'" + employee_name + "','" + employee_paswd + "',DEFAULT,3)";
		if (mysql_query(conn, ins.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}

	}
}


int main() {

	MYSQL* conn;
	conn = program_start(HOST,USER,PW,DB);

	add_initial_data(conn);


	bool exit = false;

	while (!exit) {

		system("cls");

		int choice;
		cout << "\n\t\t\t || Welcome To Car Rental System ||\n" << endl;
		cout << "1. login as Customer." << endl;
		cout << "2. login as Employee." << endl;
		cout << "3. login as Manager." << endl;
		cout << "4. exit." << endl;
		cout << "Enter Choice: ";

		if (!check_int(choice)) continue;

		string  name, paswd;
		int id;

		if (choice == 1 || choice == 2 || choice == 3) {

			cout << "Enter your Name : ";
			cin >> name;
			cout << "Enter your ID : ";

			if (!check_int(id)) continue;

			cout << "Enter your Password : ";
			cin >> paswd;
		}


		if (choice == 1) {

			if (check_user(conn, id, paswd)) {
				customer cus_obj(name, id, paswd);
				cus_obj.customer_functions(conn);
			}
			else {
				cout << "\n\t\t\t Incorrect details \n" << endl;
				Sleep(2000);
			}
		}
		else if (choice == 2) {

			if (check_user(conn, id, paswd)) {
				employee emp_obj(name, id, paswd);
				emp_obj.employee_functions(conn);
			}
			else {
				cout << "\n\t\t\t Incorrect details \n" << endl;
				Sleep(2000);
			}

		}
		else if (choice == 3) {

			if (name == MANAGER_NAME && id == MANAGER_ID && paswd == MANAGER_PASWD) {
				manager mgr_obj(name, id, paswd);
				mgr_obj.modify_records(conn);
			}
			else {
				cout << "\n\t\t\t Incorrect details \n" << endl;
				Sleep(2000);
			}

		}
		else if (choice == 4) {
			exit = true;
		}
		else {
			cout << "\n\t\t\t Please Enter a Valid Choice  \n" << endl;
			Sleep(2000);
		}


	}
	return 0;
}

