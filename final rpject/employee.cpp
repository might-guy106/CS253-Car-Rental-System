#include "common_functions.hpp"
#include "employee.hpp"
#include "user.hpp"
using namespace std;


/* -----------------------------------------------------------     employee cunstructor    ----------------------------------------------------------- */

employee::employee(string name, int id, string pswd) {
	Name = name;
	ID = id;
	Password = pswd;
}

/* -----------------------------------------------------------    Display Available Cars      ----------------------------------------------------------- */

void employee::display_avail_cars(MYSQL* conn) {

	cout << "\t\t-----------------------------------" << "\n";
	cout << "\t\t" << setw(10) << "Model" << setw(10) << "Cond" << setw(10) << "Price" << endl;
	cout << "\t\t-----------------------------------" << "\n";

	string dis = "SELECT Model,Cond,Price FROM Cars WHERE Availability=1 ";
	if (mysql_query(conn, dis.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			int num = mysql_num_fields(res);
			int row_count = mysql_num_rows(res);

			if (row_count > 0) {

				MYSQL_ROW row;
				while (row = mysql_fetch_row(res)) {
					cout << "\t\t";
					for (int i = 0; i < num; i++) {
						cout << setw(10) << row[i];
					}
					cout << "\n" << endl;
				}
				cout << "\t\t-----------------------------------" << "\n" << endl;
			}
			else cout << "\t\t\t\tNO Availabe Cars\n" << endl;
		}
		mysql_free_result(res);
	}

}

/* -----------------------------------------------------------    Display rentings    ----------------------------------------------------------- */

void employee::display_my_rentings(MYSQL* conn) {

	stringstream ss;
	ss << ID;
	string temp_ID = ss.str();

	string dis = "SELECT Model,Price,Dispatch_Date,Due_Date FROM Cars WHERE Rented_By_ID=" + temp_ID + " ";
	if (mysql_query(conn, dis.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			int num = mysql_num_fields(res);
			int row_count = mysql_num_rows(res);

			if (row_count > 0) {

				cout << "\t-------------------------------------------------------" << "\n";
				cout << "\t" << setw(10) << "Model" << setw(10) << "Price" << setw(15) << "Dispatch_Date" << setw(15) << "Due_Date" << endl;
				cout << "\t-------------------------------------------------------" << "\n";

				MYSQL_ROW row;
				while (row = mysql_fetch_row(res)) {
					cout << "\t";
					for (int i = 0; i < num; i++) {
						if (row[i] == NULL) cout << setw(15) << "NULL";
						else if (i >= 2) cout << setw(15) << row[i];
						else cout << setw(10) << row[i];
					}
					cout << "\n" << endl;
				}
				cout << "\t-------------------------------------------------------" << "\n" << endl;
			}
			else cout << "\t\t\t\tNO Rentings\n" << endl;
		}
		mysql_free_result(res);
	}

}

/* -----------------------------------------------------------    Rent car    ----------------------------------------------------------- */

void employee::rent_request(MYSQL* conn) {

	stringstream ss;
	ss << ID;
	string temp_ID = ss.str();

	if (check_user_eligibility(conn,temp_ID,"Employees")) {
		string car_model;
		cout << "Enter Car Model : ";
		cin >> car_model;

		int price_avail = -1;


		if (check_car_availability(conn, car_model, price_avail)) {

			int confirm_booking;
			cout << "\t\t\tCar is available for " << price_avail << "Rs." << endl;
			cout << "1.  Confirm Booking" << endl;
			cout << "2.  Terminate Booking\n" << endl;
			cout << "Enter Choice: ";

			if (!check_int(confirm_booking)) return;

			if (confirm_booking == 1) {

				string dispatch_date, due_date;
				cout << "Enter Today's date (YYYY-MM-DD) : ";
				cin >> dispatch_date;
				cout << "Enter returning date (YYYY-MM-DD) : ";
				cin >> due_date;

				string upd = " UPDATE cars SET Rented_By_ID=" + temp_ID + ",Availability=0,Dispatch_Date='" + dispatch_date + "',Due_Date='" + due_date + "' WHERE Model='" + car_model + "' AND Availability=1 ORDER BY Price ASC LIMIT 1";
				if (mysql_query(conn, upd.c_str())) {
					cout << "Error: " << mysql_error(conn) << endl;
				}
				else {
					cout << "\n\t\tYour car : " + car_model + " is booked \n" << endl;
				}
			}
			else if (confirm_booking == 2) {

			}
			else {
				cout << "\n\t\t\t Please Enter a Valid Input \n" << endl;
			}
		}
		else {
			cout << "\n\t\t\t no such car is available \n" << endl;
		}
	}
	else {
		cout << "\n\t\t\t Your Quto for renting cars is over \n" << endl;
	}

}

/* -----------------------------------------------------------    Return car    ----------------------------------------------------------- */

void employee::return_request(MYSQL* conn) {

	string car_model, return_date;
	int new_cond;
	cout << "Enter Car Model : ";
	cin >> car_model;
	cout << "Car condition at return ";
	cout << "1.  worst" << endl;
	cout << "2.  bad" << endl;
	cout << "3.  decent" << endl;
	cout << "4.  good" << endl;
	cout << "5.  excellent\n" << endl;
	cout << "Enter Choice: ";

	if (!check_int(new_cond)) return;

	cout << "Enter Returning Date (YYYY_MM_DD) : ";
	cin >> return_date;

	stringstream as;
	as << new_cond;
	string temp_new_cond = as.str();

	stringstream ss;
	ss << ID;
	string temp_ID = ss.str();

	if (check_return_car(conn, car_model, temp_ID)) {

		update_user(conn, car_model, temp_ID, new_cond, return_date,"Employees");
		update_car(conn, car_model, temp_new_cond, temp_ID);

	}
	else cout << "\n\t\t\t NO Such Renting exist \n" << endl;
}

/* -----------------------------------------------------------    Clear due     ----------------------------------------------------------- */

void employee::clear_due_request(MYSQL* conn) {

	stringstream ss;
	ss << ID;
	string temp_ID = ss.str();

	display_due(conn, temp_ID,"Employees");

	int choice;
	cout << "1.  Clear Due" << endl;
	cout << "2.  Go back.\n" << endl;
	cout << "Enter Choice: ";
	if (!check_int(choice)) return;

	if (choice == 1) {

		string upd = "UPDATE Employees SET Fine_Due=0 WHERE ID=" + temp_ID + "";
		if (mysql_query(conn, upd.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\t\t Your Due is Cleared \n" << endl;
		}

	}

}

/* -----------------------------------------------------------    employee_functions    ----------------------------------------------------------- */

void employee::employee_functions(MYSQL* conn) {

	bool employee_exit = false;
	while (!employee_exit) {

		system("cls");

		int val;
		cout << "\n\t\t\t || Employee " + Name + " ||\n" << endl;
		cout << "1.  Display Available Cars." << endl;
		cout << "2.  Display My Rentings." << endl;
		cout << "3.  Rent a Car." << endl;
		cout << "4.  Return a Car." << endl;
		cout << "5.  Clear My Dues." << endl;
		cout << "6.  Logout.\n" << endl;
		cout << "Enter Choice: ";
		if (!check_int(val)) return;

		if (val == 1) {
			display_avail_cars(conn);
			Sleep(5000);
		}
		else if (val == 2) {
			display_my_rentings(conn);
			Sleep(5000);
		}
		else if (val == 3) {
			rent_request(conn);
			Sleep(2000);
		}
		else if (val == 4) {
			return_request(conn);
			Sleep(2000);
		}
		else if (val == 5) {
			clear_due_request(conn);
			Sleep(2000);
		}
		else if (val == 6) {
			employee_exit = true;
		}
		else {
			cout << "\n\t\t\t Please Enter a Valid Input \n" << endl;
			Sleep(2000);
		}

	}

}



