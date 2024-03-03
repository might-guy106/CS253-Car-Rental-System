#include "common_functions.hpp"
#include "manager.hpp"
#include "user.hpp"
using namespace std;

/****************************   Manager Class Start   ********************************/

manager::manager(string name, int id, string pswd) {
	Name = name;
	ID = id;
	Password = pswd;
}


void manager::display_cars(MYSQL* conn) {

	string colnames = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Cars' ORDER BY ORDINAL_POSITION";
	if (mysql_query(conn, colnames.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			int col = 0;

			MYSQL_ROW row;
			cout << "--------------------------------------------------------------------------------------------------" << endl;
			while (row = mysql_fetch_row(res)) {
				col++;
				if(col>=5) cout << setw(15) << row[0];
				else cout << setw(10) << row[0];
			}
			cout << "\n--------------------------------------------------------------------------------------------------" << endl;
		}
		mysql_free_result(res);

	}

	string dis = "SELECT * FROM Cars";
	if (mysql_query(conn, dis.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			int num = mysql_num_fields(res);

			MYSQL_ROW row;
			cout << "\n";
			while (row = mysql_fetch_row(res)) {
				for (int i = 0; i < num; i++) {
					if (row[i] == NULL) cout << setw(15) << "NULL";
					else if(i>=4)  cout << setw(15) << row[i];
					else cout << setw(10) << row[i];
				}
				cout  << endl;
			}
			cout << "--------------------------------------------------------------------------------------------------" << "\n" << endl;
		}
		mysql_free_result(res);
	}
}


	void manager::add_car(MYSQL * conn,int& car_id, string & model, int& cond, int& price) {

		stringstream bs;
		bs << car_id;
		string temp_car_id = bs.str();

		stringstream ss;
		ss << cond;
		string temp_cond = ss.str();

		stringstream as;
		as << price;
		string temp_price = as.str();

		string ins = "INSERT INTO Cars (ID,Model,Cond,Price,Availability,Rented_By_ID,Dispatch_Date,Due_Date) VALUES ( "+temp_car_id+",'" + model + "' , " + temp_cond + " , " + temp_price + " , DEFAULT ,DEFAULT,DEFAULT , DEFAULT )";
		if (mysql_query(conn, ins.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\tCar '" << model << "' Inserted Successfuly!\n" << endl;
		}

	}

	void manager::delete_car(MYSQL* conn,int &car_id) {

		stringstream bs;
		bs << car_id;
		string temp_car_id = bs.str();


		string del = "DELETE FROM Cars WHERE ID=" + temp_car_id + "";
		if (mysql_query(conn, del.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\tCar '" << car_id << "' Deleted Successfuly!\n" << endl;
		}
	}

	void manager::update_car(MYSQL* conn, int& car_id) {

		string model;
		int new_cond,price;

		cout << "Enter model of the car : ";
		cin >> model;
		cout << "Car condition ";
		cout << "1.  worst" << endl;
		cout << "2.  bad" << endl;
		cout << "3.  decent" << endl;
		cout << "4.  good" << endl;
		cout << "5.  excellent\n" << endl;
		cout << "Enter Choice: ";
		if (!check_int(new_cond)) return;

		if (new_cond < 1 || new_cond>5) {
			cout << "\n\t\t\t Invalid condition of Car \n" << endl;
			Sleep(2000);
			return;
		}

		cout << "Enter price of the car : ";
		if (!check_int(price)) return;

		stringstream bs;
		bs << car_id;
		string temp_car_id = bs.str();

		stringstream ss;
		ss << new_cond;
		string temp_new_cond = ss.str();

		stringstream as;
		as << price;
		string temp_price = as.str();

		string upd = " UPDATE cars SET Model='"+model+"',Cond="+temp_new_cond+",Price="+temp_price+" WHERE ID=" + temp_car_id + "";
		if (mysql_query(conn, upd.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\tYour car is updated \n" << endl;
		}

		


	}

	void manager::display_customers(MYSQL* conn) {

		string colnames = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Customers' ORDER BY ORDINAL_POSITION";
		if (mysql_query(conn, colnames.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {

			MYSQL_RES* res;
			res = mysql_store_result(conn);

			if (res) {

				int col = 0;

				MYSQL_ROW row;
				cout << "-------------------------------------------------------------------" << endl;
				while (row = mysql_fetch_row(res)) {
					col++;
					if (col == 2 || col == 3 ) cout << setw(15) << row[0];
					else cout << setw(10) << row[0];
				}
				cout << "\n-------------------------------------------------------------------" << endl;
			}
			mysql_free_result(res);

		}

		string dis = "SELECT * FROM Customers";
		if (mysql_query(conn, dis.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {

			MYSQL_RES* res;
			res = mysql_store_result(conn);

			if (res) {

				int num = mysql_num_fields(res);

				MYSQL_ROW row;
				cout << "\n";
				while (row = mysql_fetch_row(res)) {
					for (int i = 0; i < num; i++) {
						if (i == 1 || i == 2)  cout << setw(15) << row[i];
						else cout << setw(10) << row[i];
					}
					cout << endl;
				}
				cout << "-------------------------------------------------------------------" << "\n" << endl;
			}
			mysql_free_result(res);
		}
	}

	void manager::add_customer(MYSQL* conn, string& name, int& id, string& paswd) {

		stringstream ss;
		ss << id;
		string temp_id = ss.str();

		int avg = average_customer_score(conn);

		stringstream as;
		as << avg;
		string temp_avg = as.str();

		string ins = "INSERT INTO Customers (ID,Name,Password,Fine_Due,Score) VALUES ( " + temp_id + ",'" + name + "','" + paswd + "',DEFAULT,"+temp_avg+" )";
		if (mysql_query(conn, ins.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\tCustomer '" << name << "' Inserted Successfuly!\n" << endl;
		}


	}

	void manager::delete_customer(MYSQL* conn) {

		string id;
		cout << "Enter ID of the Customer : ";
		cin >> id;

		string del = "DELETE FROM Customers WHERE ID='" + id + "'";
		if (mysql_query(conn, del.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\t Customer '" << id << "' Deleted Successfuly!\n" << endl;
		}

	}

	void manager::update_customer(MYSQL* conn,int& customer_id) {

		string name, paswd;

		cout << "Enter Name of the Customer : ";
		cin >> name;
		cout << "Enter Password of the Customer : ";
		cin >> paswd;

		stringstream bs;
		bs << customer_id;
		string temp_customer_id = bs.str();


		string upd = "UPDATE Customers SET Name='" + name + "',Password='" + paswd + "' WHERE ID=" + temp_customer_id + "";
		if (mysql_query(conn, upd.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\t\tCustomer is updated \n" << endl;
		}
	}

	void manager::display_employees(MYSQL* conn) {

		string colnames = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Employees' ORDER BY ORDINAL_POSITION";
		if (mysql_query(conn, colnames.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {

			MYSQL_RES* res;
			res = mysql_store_result(conn);

			if (res) {

				int col = 0;

				MYSQL_ROW row;
				cout << "-------------------------------------------------------------------" << endl;
				while (row = mysql_fetch_row(res)) {
					col++;
					if (col == 2 || col == 3) cout << setw(15) << row[0];
					else cout << setw(10) << row[0];
				}
				cout << "\n-------------------------------------------------------------------" << endl;
			}
			mysql_free_result(res);

		}

		string dis = "SELECT * FROM Employees";
		if (mysql_query(conn, dis.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {

			MYSQL_RES* res;
			res = mysql_store_result(conn);

			if (res) {

				int num = mysql_num_fields(res);

				MYSQL_ROW row;
				cout << "\n";
				while (row = mysql_fetch_row(res)) {
					for (int i = 0; i < num; i++) {
						if (i == 1 || i == 2)  cout << setw(15) << row[i];
						else cout << setw(10) << row[i];
					}
					cout << endl;
				}
				cout << "-------------------------------------------------------------------" << "\n" << endl;
			}
			mysql_free_result(res);
		}
	}

	void manager::add_employee(MYSQL* conn, string& name, int& id, string& paswd) {

		stringstream ss;
		ss << id;
		string temp_id = ss.str();

		int avg = average_customer_score(conn);

		stringstream as;
		as << avg;
		string temp_avg = as.str();

		string ins = "INSERT INTO Employees (ID,Name,Password,Fine_Due,Score) VALUES ( " + temp_id + ",'" + name + "','" + paswd + "',DEFAULT,"+ temp_avg +")";
		if (mysql_query(conn, ins.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\t Employee '" << name << "' Inserted Successfuly!\n" << endl;
		}
	}

	void manager::delete_employee(MYSQL* conn) {

		string id;
		cout << "Enter ID of the Employee : ";
		cin >> id;

		string del = "DELETE FROM Employees WHERE ID=" + id + "";
		if (mysql_query(conn, del.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\t Employee '" << id << "' Deleted Successfuly!\n" << endl;
		}
	}

	void manager::update_employee(MYSQL* conn, int& customer_id) {

		string name, paswd;

		cout << "Enter Name of the Customer : ";
		cin >> name;
		cout << "Enter Password of the Customer : ";
		cin >> paswd;

		stringstream bs;
		bs << customer_id;
		string temp_customer_id = bs.str();


		string upd = "UPDATE Customers SET Name='" + name + "',Password='" + paswd + "' WHERE ID=" + temp_customer_id + "";
		if (mysql_query(conn, upd.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\t\tCustomer is updated \n" << endl;
		}
	}

	void manager::modify_records(MYSQL* conn) {

		bool manager_exit = false;
		while (!manager_exit) {

			system("cls");

			int val;
			cout << "\n\t\t\t || Manager Pankaj ||\n" << endl;
			cout << "1.  Cars." << endl;
			cout << "2.  Customers." << endl;
			cout << "3.  Employee." << endl;
			cout << "4.  Logout.\n" << endl;
			cout << "Enter Choice: ";
			cin >> val;


			if (val == 1) {

				bool cars_exit = false;
				while (!cars_exit) {

					system("cls");

					int choice_car;
					cout << "\n\t\t\t || Operations on Cars ||\n" << endl;
					cout << "1.  Display Cars." << endl;
					cout << "2.  Add Car." << endl;
					cout << "3.  Delete Car." << endl;
					cout << "4.  Update Car" << endl;
					cout << "5.  Go back.\n" << endl;
					cout << "Enter Choice: ";
					cin >> choice_car;


					if (choice_car == 1) {
						display_cars(conn);
						Sleep(5000);
					}
					else if (choice_car == 2) {

						string model;
						int car_id,cond, price;

						cout << "Enter ID of the car : ";
						if (!check_int(car_id)) continue;

						if (!(car_id < 2000 && car_id >= 1000)) {
							cout << "\n\t\t\t Invalid id for Car type \n" << endl;
							Sleep(2000);
							continue;
						}
						if (!check_id(conn, car_id)) {

							cout << "Enter model of the car : ";
							cin >> model;
							cout << "Car condition ";
							cout << "1.  worst" << endl;
							cout << "2.  bad" << endl;
							cout << "3.  decent" << endl;
							cout << "4.  good" << endl;
							cout << "5.  excellent\n" << endl;
							cout << "Enter Choice: ";
							if (!check_int(cond)) continue;

							if (cond < 1 || cond>5) {
								cout << "\n\t\t\t Invalid condition of Car \n" << endl;
								Sleep(2000);
								continue;
							}

							cout << "Enter price of the car : ";
							if (!check_int(price)) continue;

							add_car(conn,car_id, model, cond, price);
							Sleep(2000);
						}
						else {
							cout << "\n\t\t\t This CAR_ID already exists \n" << endl;
						}
						Sleep(2000);

					}
					else if (choice_car == 3) {

						int car_id;

						cout << "Enter ID of the car : ";
						if (!check_int(car_id)) return;

						if (check_id(conn, car_id)) {
							delete_car(conn,car_id);
						}
						else {
							cout << "\n\t\t\t This CAR_ID does not exists \n" << endl;
						}
						Sleep(2000);
					}
					else if (choice_car == 4) {

						int car_id;

						cout << "Enter ID of the car : ";
						if (!check_int(car_id)) return;

						if (check_id(conn, car_id)) {
							update_car(conn,car_id);
						}
						else {
							cout << "\n\t\t\t This CAR_ID does not exists \n" << endl;
						}
						Sleep(2000);

					}
					else if (choice_car == 5) {
						cars_exit = true;
					}
					else {
						cout << "\n\t\t\t Please Enter a Valid Input \n" << endl;
						Sleep(2000);
					}
				}
			}
			else if (val == 2) {

				bool customer_exit = false;
				while (!customer_exit) {

					system("cls");

					int choice_customer;
					cout << "\n\t\t\t || Operations on Customers ||\n" << endl;
					cout << "1.  Display Customers." << endl;
					cout << "2.  Add Customer." << endl;
					cout << "3.  Delete Customer." << endl;
					cout << "4.  Update Customer." << endl;
					cout << "5.  Go back.\n" << endl;
					cout << "Enter Choice: ";
					cin >> choice_customer;

					if (choice_customer == 1) {
						display_customers(conn);
						Sleep(5000);
					}
					else if (choice_customer == 2) {

						string name, paswd;
						int id;

						cout << "Enter Name of the Customer : ";
						cin >> name;
						cout << "Enter ID of the Customer : ";
						cin >> id;

						if (!(id < 3000 && id >= 2000)) {
							cout << "\n\t\t\t Invalid id for Customer type \n" << endl;
							Sleep(2000);
							continue;
						}
						if (!check_id(conn, id)) {
							cout << "Enter Password of the Customer : ";
							cin >> paswd;

							add_customer(conn, name, id, paswd);
						}
						else {
							cout << "\n\t\t\t This ID already exists \n" << endl;
						}
						Sleep(2000);
					}
					else if (choice_customer == 3) {
						delete_customer(conn);
						Sleep(2000);
					}
					else if (choice_customer == 4) {

						int customer_id;

						cout << "Enter ID of the customer : ";
						if (!check_int(customer_id)) return;

						if (check_id(conn, customer_id)) {
							update_customer(conn, customer_id);
						}
						else {
							cout << "\n\t\t\t This customer ID does not exists \n" << endl;
						}
						Sleep(2000);
					}
					else if (choice_customer == 5) {
						customer_exit = true;
					}
					else {
						cout << "\n\t\t\t Please Enter a Valid Input \n" << endl;
						Sleep(2000);
					}
				}
			}
			else if (val == 3) {

				bool employee_exit = false;
				while (!employee_exit) {

					system("cls");

					int choice_employee;
					cout << "\n\t\t\t || Operations on Employees ||\n" << endl;
					cout << "1.  Display Employees." << endl;
					cout << "2.  Add Employee." << endl;
					cout << "3.  Delete Employee." << endl;
					cout << "4.  Update Customer." << endl;
					cout << "5.  Go back.\n" << endl;
					cout << "Enter Choice: ";
					cin >> choice_employee;

					if (choice_employee == 1) {
						display_employee(conn);
						Sleep(5000);
					}
					else if (choice_employee == 2) {

						string name, paswd;
						int id;

						cout << "Enter Name of the Employee : ";
						cin >> name;
						cout << "Enter ID of the Employee : ";
						cin >> id;

						if (!(id < 4000 && id >= 3000)) {
							cout << "\n\t\t\t Invalid id for Employee type \n" << endl;
							Sleep(2000);
							continue;
						}

						if (!check_id(conn, id)) {
							cout << "Enter Password of the Employee : ";
							cin >> paswd;

							add_employee(conn, name, id, paswd);
						}
						else {
							cout << "\n\t\t\t This ID already exists \n" << endl;
						}
						Sleep(2000);
					}
					else if (choice_employee == 3) {
						delete_employee(conn);
						Sleep(2000);
					}
					else if (choice_employee == 4) {

						int employee_id;

						cout << "Enter ID of the employee : ";
						if (!check_int(employee_id)) return;

						if (check_id(conn, employee_id)) {
							update_employee(conn, employee_id);
						}
						else {
							cout << "\n\t\t\t This customer ID does not exists \n" << endl;
						}
						Sleep(2000);
					}
					else if (choice_employee == 5) {
						employee_exit = true;
					}
					else {
						cout << "\n\t\t\t Please Enter a Valid Input \n" << endl;
						Sleep(2000);
					}
				}
			}
			else if (val == 4) {
				manager_exit = true;
			}
			else {
				cout << "\n\t\t\t Please Enter a Valid Input \n" << endl;
				Sleep(2000);
			}

		}

	}












	
