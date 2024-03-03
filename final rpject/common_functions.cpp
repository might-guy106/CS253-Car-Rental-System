#include "common_functions.hpp"

bool check_int(int &var) {

	try {
		cin >> var;

		if (cin.fail()) {
			std::cin.clear(); // clear the error flag
			std::cin.ignore(100000, '\n'); // discard the input buffer
			throw std::invalid_argument("Invalid input type. Please enter an integer.");
		}
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Warning: " << e.what() << std::endl;
		Sleep(2000);
		return false;
	}
	return true;
}

/****************************   daysBetween  START  ********************************/

vector<string> split(const string& str, char delimiter) {
	vector<string> tokens;
	string token;
	istringstream stream(str);

	while (getline(stream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

bool isLeapYear(int year) {
	if (year % 400 == 0) {
		return true;
	}
	else if (year % 100 == 0) {
		return false;
	}
	else if (year % 4 == 0) {
		return true;
	}
	return false;
}

int daysBetween(const string date1, const string date2) {
	// Split the dates into tokens
	vector<string> tokens1 = split(date1, '-');
	vector<string> tokens2 = split(date2, '-');

	// Convert tokens to integers
	int year1 = stoi(tokens1[0]);
	int month1 = stoi(tokens1[1]);
	int day1 = stoi(tokens1[2]);

	int year2 = stoi(tokens2[0]);
	int month2 = stoi(tokens2[1]);
	int day2 = stoi(tokens2[2]);

	// Calculate total days for each year
	int days1 = 0;
	for (int i = 1; i < year1; ++i) {
		days1 += 365 + (isLeapYear(i) ? 1 : 0);
	}

	int days2 = 0;
	for (int i = 1; i < year2; ++i) {
		days2 += 365 + (isLeapYear(i) ? 1 : 0);
	}

	// Calculate days for current year months
	days1 += (isLeapYear(year1) && month1 > 2) ? 1 : 0;  // Add 1 day for leap year after Feb
	days2 += (isLeapYear(year2) && month2 > 2) ? 1 : 0;

	// Add days for current month and day
	for (int i = 1; i < month1; ++i) {
		switch (i) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days1 += 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days1 += 30;
			break;
		case 2:
			days1 += 28;
			break;
		}
	}

	for (int i = 1; i < month2; ++i) {
		switch (i) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days2 += 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days2 += 30;
			break;
		case 2:
			days2 += 28;
			break;
		}
	}

	days1 += day1;
	days2 += day2;

	return days2 - days1;
}

bool check_id(MYSQL* conn, int id) {

	string table;
	if (id < 2000 && id>1000) table = "Cars";
	else if (id < 3000 && id>2000) table = "Customers";
	else if (id < 4000 && id >> 3000) table = "Employees";


	stringstream ss;
	ss << id;
	string temp_id = ss.str();

	string quer = "SELECT * FROM "+table+" WHERE ID=" + temp_id + "";
	if (mysql_query(conn, quer.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			int row_count = mysql_num_rows(res);
			if (row_count == 0) return false;
			else return true;

		}
		mysql_free_result(res);
	}

}

bool check_user(MYSQL* conn, int id, string paswd) {

	string user_table;
	if (id >= 2000 && id < 3000) user_table = "Customers";
	else user_table = "Employees";

	stringstream ss;
	ss << id;
	string temp_id = ss.str();

	string quer = "SELECT Password FROM "+user_table+" WHERE ID=" + temp_id + "";
	if (mysql_query(conn, quer.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {
		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {
			int row_count = mysql_num_rows(res);
			if (row_count == 0) return false;
			else if (row_count == 1) {

				MYSQL_ROW row;
				row = mysql_fetch_row(res);
				if (paswd == row[0]) return true;
				else return false;
			}
		}
	}

}

bool check_car_availability(MYSQL* conn, string car_model, int& price_avail) {

	string quer = "SELECT Price FROM Cars WHERE Model='" + car_model + "' AND Availability=1 ORDER BY Price ASC LIMIT 1";
	if (mysql_query(conn, quer.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			int row_count = mysql_num_rows(res);

			if (row_count > 0) {

				MYSQL_ROW row;
				row = mysql_fetch_row(res);
				price_avail = atoi(row[0]);
				return true;
			}
			else return false;

		}
		mysql_free_result(res);
	}
}

bool check_user_eligibility(MYSQL* conn, string temp_ID, string user_table) {

	int score, cars_rented;

	string quer1 = "SELECT Score FROM "+user_table+" WHERE ID=" + temp_ID + "";
	if (mysql_query(conn, quer1.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			MYSQL_ROW row;
			row = mysql_fetch_row(res);
			score = atoi(row[0]);

		}
		mysql_free_result(res);
	}

	string quer2 = "SELECT * FROM Cars WHERE Rented_By_ID=" + temp_ID + "";
	if (mysql_query(conn, quer2.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {
			cars_rented = mysql_num_rows(res);
		}
		mysql_free_result(res);
	}

	if (cars_rented < score) return true;
	else return false;


}

bool check_return_car(MYSQL* conn, string car_model, string temp_ID)
{
	string quer = "SELECT * FROM cars WHERE Model='" + car_model + "' AND Rented_By_ID=" + temp_ID + " ";
	if (mysql_query(conn, quer.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			int row_count = mysql_num_rows(res);

			if (row_count > 0) return true;
			else return false;
		}
		mysql_free_result(res);
	}
}


void get_car_details(MYSQL* conn, string car_model, string temp_ID, int& car_cond, int& car_price, string& dispatch_date, string& due_date) {

	string quer = "SELECT Cond,Price,Dispatch_Date,Due_Date FROM cars WHERE Model='" + car_model + "' AND Rented_By_ID=" + temp_ID + " ORDER BY Price DESC LIMIT 1";
	if (mysql_query(conn, quer.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			MYSQL_ROW row;
			row = mysql_fetch_row(res);

			car_cond = atoi(row[0]);
			car_price = atoi(row[1]);
			dispatch_date = row[2];
			due_date = row[3];

		}
		mysql_free_result(res);
	}

}

void get_user_details(MYSQL* conn, string temp_ID, int& curr_due, int& score,string user_table) {

	string quer = "SELECT Fine_Due,Score FROM "+user_table+" WHERE ID=" + temp_ID + "";
	if (mysql_query(conn, quer.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {
		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			MYSQL_ROW row;
			row = mysql_fetch_row(res);
			curr_due = atoi(row[0]);
			score = atoi(row[1]);
		}
		mysql_free_result(res);
	}

}

void update_user(MYSQL* conn, string car_model, string temp_ID, int new_cond, string return_date,string user_table) {

	int car_price, car_cond;
	string dispatch_date, due_date;

	get_car_details(conn, car_model, temp_ID, car_cond, car_price, dispatch_date, due_date);

	int curr_due, score;
	get_user_details(conn,temp_ID, curr_due, score,user_table);

	int days1 = daysBetween(due_date, return_date);
	int days2 = daysBetween(dispatch_date, return_date);

	int new_due = curr_due + (car_price * (days2 - days1)) + ((car_price * 1.1) * days1);

	if (days1 <= 0) new_due = curr_due + (car_price * days2);
	else new_due = curr_due + (car_price * (days2 - days1)) + ((car_price * 1.1) * days1);

	cout << "\n\t\t\tcurr_due :" << curr_due << endl;
	cout << "\t\t\tfine days :" << days1 << endl;
	
	if(days1<=0) cout << "\t\t\tnormal days :" << days2 << endl;
	else cout << "\t\t\tnormal days :" << (days2 - days1) << endl;
	
	if (days1 <= 0) cout << "\t\t\tnormal rent : " << (car_price * days2) << endl;
	else  cout << "\t\t\tnormal rent : " << (car_price * (days2 - days1)) << endl;

	if (days1 <= 0) cout << "\t\t\tfine  : " << 0 << endl;
	else  cout << "\t\t\tfine  : " << ((car_price * 1.1) * days1) << endl;

	cout << "\t\t\tnew_due :" << new_due << endl;

	if (days2 >= 0) {

		if (days1 > 0 && score > 1) score--;

		if (new_cond < car_cond && score > 1) score--;
		else if (new_cond >= car_cond && score < 5) score++;


		stringstream as;
		as << score;
		string temp_score = as.str();

		stringstream ss;
		ss << new_due;
		string temp_new_due = ss.str();

		string upd = "UPDATE "+user_table+" SET Fine_Due=" + temp_new_due + ",Score=" + temp_score + " WHERE ID=" + temp_ID + "";
		if (mysql_query(conn, upd.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
		}
		else {
			cout << "\n\t\t\tdue and score are updated \n" << endl;
		}
		Sleep(3000);
	}
	else cout << "\n\t\t\tInvalid return date \n" << endl;


}

void update_car(MYSQL* conn, string car_model, string temp_new_cond, string temp_ID) {

	string upd = " UPDATE cars SET Rented_By_ID=NULL,Availability=1,Due_Date=NULL WHERE Model='" + car_model + "' AND Rented_By_ID=" + temp_ID + " ORDER BY Price DESC LIMIT 1";
	if (mysql_query(conn, upd.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {
		cout << "\n\t\tYour car : " + car_model + " is returned \n" << endl;
	}
}


void display_due(MYSQL* conn, string temp_ID,string user_table) {

	string quer = "SELECT Fine_Due FROM "+user_table+" WHERE ID=" + temp_ID + "";
	if (mysql_query(conn, quer.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {
		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			MYSQL_ROW row;
			row = mysql_fetch_row(res);
			int due = atoi(row[0]);

			cout << "\n\t\t\t Your current Due is : " << due << "\n" << endl;
		}
		mysql_free_result(res);
	}
}

int average_customer_score(MYSQL* conn) {

	int avg;

	string quer = "SELECT AVG(Score) FROM Customers";
	if (mysql_query(conn, quer.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			MYSQL_ROW row;
			row = mysql_fetch_row(res);

			avg = round(atof(row[0]));
		}
		mysql_free_result(res);
	}
	return avg;
}

int average_employee_score(MYSQL* conn) {

	int avg;

	string quer = "SELECT AVG(Score) FROM Employees";
	if (mysql_query(conn, quer.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {

		MYSQL_RES* res;
		res = mysql_store_result(conn);

		if (res) {

			MYSQL_ROW row;
			row = mysql_fetch_row(res);

			avg = round(atof(row[0]));
		}
		mysql_free_result(res);
	}
	return avg;
}


MYSQL* program_start(const char* HOST, const char* USER, const char* PW, const char* DB) {

	// connecting Database
	MYSQL* conn;
	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) { //attempts to establish a connection to a MySQL server running on host.
		cout << "Error: " << mysql_error(conn) << endl;                 // to display connection error if any 
	}
	else {
		cout << "Logged In Database!" << endl;
	}

	// creating Customers Table
	stringstream as;
	as << "CREATE TABLE IF NOT EXISTS Customers ( ID INT NOT NULL UNIQUE , Name VARCHAR(100) NOT NULL , Password VARCHAR(100) NOT NULL,Fine_Due INT DEFAULT 0,  Score INT DEFAULT 5)";
	string customer_table = as.str();

	if (mysql_query(conn, customer_table.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {
		cout << "Customers TABLE created Successfuly!" << endl;
	}

	// creating Cars Table // revert back
	stringstream bs;
	bs << "CREATE TABLE IF NOT EXISTS Cars ( ID INT NOT NULL UNIQUE ,Model VARCHAR(100) NOT NULL, Cond INT NOT NULL , Price INT DEFAULT 2000 ,  Availability INT DEFAULT 1, Rented_By_ID INT  , Dispatch_Date DATE , Due_Date DATE   )";
	string car_table = bs.str();

	if (mysql_query(conn, car_table.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {
		cout << "Cars TABLE created Successfuly!" << endl;
	}

	// creating Employees Table
	stringstream cs;
	cs << "CREATE TABLE IF NOT EXISTS Employees ( ID INT NOT NULL UNIQUE , Name VARCHAR(100) NOT NULL , Password VARCHAR(100) NOT NULL,Fine_Due INT DEFAULT 0, Score INT DEFAULT 5)";
	string employee_table = cs.str();

	if (mysql_query(conn, employee_table.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else {
		cout << "Employees TABLE created Successfuly!" << endl;
	}

	return conn;
}

