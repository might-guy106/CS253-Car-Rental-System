<!-- ABOUT THE PROJECT -->
# Table of Contents

1. [About The Project](#section-1)
2. [Getting Started](#section-2)
3. [Working](#section-3)
4. [Customer Options](#section-4)
5. [Employee Options](#section-5)
6. [Manager Options](#section-6)
7. [Initial data](#section-7)
8. [Asumptions and Notes](#section-8)

## About The Project
<a name="section-1"></a>

car rental system in C++ language using Object-Oriented Programming concepts.

### Abbreviations

* [MF] : member function
* [HF} : helping function  ( which are defined `common_functons.cpp` ) 


### Built With

* DataBase: MySQL
* Language:C++
* Libraries: iostream,iomanip,vector,cmath,stdexcept,limits,mysql.h,mysqld_error.h,windows.h,sstream

<!-- GETTING STARTED -->
## Getting Started
<a name="section-2"></a>
### Installation

1. Install Visual Studio.
2. Install MySQL windows installer.
3. Followed the steps from this video [MySQL Installation and Setup for C++ Development on Visual Studio](https://www.youtube.com/watch?v=yNniOHn9Xe0&t=8s) to connect c++ project with MySQL server.
4. Please  follow the steps the same but instead of step 3.c, use C:\Program Files\MySQL\MySQL Connector C++ 8.0\lib64\vs14 as the directory
5. After Set-up add all the files to the c++ project connected to MySQL server.

### Modifications

* In my case first i have a created a database named: project and connected it with c++;
* to change these settings make edits in main.cpp file according to your set-up.
<div align="center">
  <img src="images/Screenshot 2024-03-03 200735.png" alt="Logo">
</div> 

* by default the manager details are set as name="manager_1",id=1,password="man1"

## Working
<a name="section-3"></a>
Project contains total 5 header files and 5 cpp files

### Header files

1. `common_functions.hpp` : this header file includes all the required libraries and declarations of all the helping functins which will further be defined in common_functions.cpp.
2. `user.hpp` : this header file contains user class which is common to cusstomer,employee and manager.
3. `customer.hpp` : this header  file defines customer class which is a child class of user.
4. `employee.hpp` : this header file defines employee class which is a child class of user.
5. `manager.hpp` : this header file defines manager class which is a child class of user.

### cpp files

1. `common_functions.cpp` : all the helping functions which are used by member functinos of all 3 user class are defined are. it also contins `program_start()` functions.
2. `customer.cpp` : defines constructor and member functions of customer class.
3. `employee.cpp` : defines constructor and member functions of employee class.
4. `manager.cpp` : defines constructor and member functions of manager class.
5. `main.cpp` : this is main file of the project.

## Customer Options
<a name="section-4"></a>
customer class member function `customer_functions()` controls all the functions below which define customer functionalities

1. Display available cars :
   * [MF] `display_avail_cars()`.
2. Display customers rentings :
   * [MF] `display_my_rentings()`.
3. Customer requests to rent a car :
   * customer class member function `rent_request()`.
   * `rent_request()` uses [HF] `check_car_availability()` to check whether a specific car requested by user is available in the Cars table.
   * `rent_request()` uses [HF] `check_user_eligibility()` to checks wether user is eligible to rent one more car.
4. Customer requests to return a car :
   * [MF] return_request()
   * `rent_request()` uses [HF]`check_return_car()` to check if user can return a specific car model.
   * `rent_request()` uses [HF] `update_user()` to update customer in Customers table with changed due and score.
   * `update_user()` [HF] `get_car_details()` to gets Details from Cars table of a the car user is returning.
   * `update_user()` [HF] `get_user_details()` to gets gets Details from Customers table of a the customer.
   * `rent_request()` [HF] `update_user()` to updates cars table.
5. Customers request to clear due :
   * customer class member function `clear_due_request()`
   * `clear_due_request()` uses helping function `display_due()` to  display current dues.

## Employee Options
<a name="section-5"></a>
employee class member function `employee_functions()` controls all the functions below which define employee functionalities

1. Display available cars :
   * [MF] `display_avail_cars()`.
2. Display customers rentings :
   * [MF] `display_my_rentings()`.
3. Employee requests to rent a car :
   * [MF] `rent_request()`.
   * `rent_request()` uses [HF] `check_car_availability()` to check whether a specific car requested by user is available in the Cars table.
   * `rent_request()` uses [HF] `check_user_eligibility()` to checks wether user is eligible to rent one more car.
4. Employee requests to return a car :
   *  [MF] return_request()
   * `rent_request()` uses [HF] `check_return_car()` to check if user can return a specific car model.
   * `rent_request()` uses [HF] `update_user()` to update customer in Customers table with changed due and score.
   * `update_user()` uses [HF] `get_car_details()` to gets Details from Cars table of a the car user is returning.
   * `update_user()` uses [HF] `get_user_details()` to gets gets Details from Customers table of a the customer.
   * `rent_request()` uses [HF] `update_user()` to updates cars table.
5. Employee request to clear due :
   * employee class member function `clear_due_request()`
   * `clear_due_request()` uses helping function `display_due()` to  display current dues.
  
## Manager Options
<a name="section-6"></a>
employee class member function `modify_records()` controls all the functions below which define manager functionalities

### On Cars 

1. display Cars table :
   * [MF] `display_cars() `
2. Add a new car :
   * [MF] `add_car()`
3. Delete a existing car :
   * [MF] `delete_car()`
   *  `delete_car()` uses [HF] `check_id()` to check whether such car id exists or not
4. Update a existing car :
   * [MF] `update_car()`
   * `update_car()` uses [HF] `check_id()` to check whether such car id exists or not

### On Customers 

1. display Customers table :
   * [MF] `display_customers() `
2. Add a new customer :
   * [MF] `add_car()`
   * `add_car()` uses [HF] `average_customer_score()` to return average customer_record value
3. Delete a existing car :
   * [MF] `delete_customer()`
   * `delete_customer()` uses [HF] `check_id()` to check whether such customer id exists or not
4. Update a existing car :
   * [MF] `update_customer()`
   * `update_customer()` uses [HF] `check_id()` to check whether such customer id exists or not

### On Employees

1. display Customers table :
   * [MF] `display_employees() `
2. Add a new customer :
   * [MF] `add_employee()`
   * `add_employee()` uses [HF] `average_employee_score()` to return average customer_record value
3. Delete a existing car :
   * [MF] `delete_customer()`
   * `delete_employee()` uses [HF] `check_id()` to check whether such customer id exists or not
4. Update a existing car :
   * [MF] `update_employee()`
   * `update_employee()` uses [HF] `check_id()` to check whether such customer id exists or not

## Initial data
<a name="section-7"></a>
uses `add_initial_data()` to add 5 cars, 5 customers, 5 employees. 

1 Manager :
* name = "manager_1"
* id = 1
* password = "man1"

5 customers :

<div align="center">
  <img src="images/customers.png" alt="Logo">
</div>

5 employees :

<div align="center">
  <img src="images/employees.png" alt="employees">
</div>

5 cars :

<div align="center">
  <img src="images/cars.png" alt="cars">
</div>

## Asumptions and Notes
<a name="section-8"></a>
* `Sleep()` function is used so please be patience to enter next choice
* each person can rent cars according to their score which lies in range 1-5
* condition is divided in 5 inters 1:worst 2:bad 3:fine 4:good 5:excellent
* score decrease by 1 if he returns after comitted date or if he returns in decreased condition than before.
* id is unique for every customer, employee and car
* car id is in range 1000-1999 , customer id is range 2000-2999 , employer id is in range 3000-3999.
* names of users, password of users and model of cars can not have whitespace in them.
* date is YYYY-MM-DD format
* while renting a car if multiple cars exist with same model then car with lowest price is shown to user.
* while returning a car if multiple cars exist with same model then car with highest price is returned.
* fine and due are added to customer Fine_Due after returningof the car.








