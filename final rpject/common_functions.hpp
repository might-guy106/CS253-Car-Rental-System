#ifndef COMMON_FUNCTIONS
#define COMMON_FUNCTIONS

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>
using namespace std;

bool check_int(int &var);                                                                     // Checks if input is of int type or not

bool check_id(MYSQL* conn, int id);                                                           // checks if such id exist or not
bool check_user(MYSQL* conn, int id, string paswd);                                           // checks if such user exist or not


/* ------------------------------------------------------------------  Helping Functions for  days between two dates   -------------------------------------------------------------------- */

vector<string> split(const string& str, char delimiter);                                      // Function to split a string into tokens based on a delimiter
bool isLeapYear(int year);                                                                    // Function to check if a year is a leap year
int daysBetween(const string date1, const string date2);                                      // Function to calculate number of days between two dates



/* ------------------------------------------------------------------  Helping Functions for  user: rent_request    ----------------------------------------------------------------------- */

bool check_car_availability(MYSQL* conn, string car_model, int& price_avail);                 // checks whether a specific car requested by user is available in the Cars table                                                                       
bool check_user_eligibility(MYSQL* conn, string temp_ID, string user_table);				  // checks wether user is eligible to rent one more car


/* ------------------------------------------------------------------  Helping Functions for  user: return_request   ---------------------------------------------------------------------- */

bool check_return_car(MYSQL* conn, string car_model, string temp_ID);                                                                         // checks if user can return a specific car model 
void get_car_details(MYSQL* conn, string car_model, string temp_ID, int& car_cond, int& car_price, string& dispatch_date, string& due_date);  // gets Details from Cars table of a the car user is returning : Cond,Price,Dispatch_Date,Due_Date
void get_user_details(MYSQL* conn, string temp_ID, int& curr_due, int& score, string user_table);                                             // gets Details from Customers table of a the customer : Fine_Due,Score
void update_user(MYSQL* conn, string car_model, string temp_ID, int new_cond, string return_date, string user_table);                         // updates customer in Customers table with changed due and score
void update_car(MYSQL* conn, string car_model, string temp_new_cond, string temp_ID);                                                         // updates cars table

/* ------------------------------------------------------------------  Helping Functions for  user: clear_due    -------------------------------------------------------------------------- */

void display_due(MYSQL* conn, string temp_ID, string user_table);                             // display current dues

/* ------------------------------------------------------------------  Helping Functions for manager: add_customer or add_employee    ----------------------------------------------------------------------- */

int average_customer_score(MYSQL* conn);                                                      // returns  average customer_record value
int average_employee_score(MYSQL* conn);                                                      // returns  average employee_record value

MYSQL* program_start(const char* HOST, const char* USER, const char* PW, const char* DB);     //connects database and creates cars,customers,employees tables

#endif // COMMON_FUNCTIONS