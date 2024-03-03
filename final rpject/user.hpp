#ifndef USER_H
#define USER_H

#include "common_functions.hpp"

using namespace std;


class user {
protected:
	string Name;
	int ID;
	string Password;
public:

	void set_Name();
	void set_ID();
	void set_Password();

	string get_Name();
	int get_ID();
	string get_Password();

};


#endif // USER_H