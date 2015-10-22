/*
 * User.h
 *
 *  Created on: Sep 30, 2015
 *      Author: Henry
 */

#ifndef USER_H_
#define USER_H_

#include "Account.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <vector>
#include <stack>
#include <unistd.h>
#include <fstream>
#include <limits.h>

class Account; // forward declaration

using namespace std;

class User {
public:
	static std::vector<User> userVec; // vector that stores all the created users
	static int uidCounter; // keeps track of the current ID count (for dummy user creation)
	string userTrace; // keeps track of what operations the user has done
	static bool execTraceBool; // status of the execution trace
	string execTrace; // the execution trace string to be written to the output file
	int userID = uidCounter; // keep consistent with the static counter (for dummy user creation)
	string accessTime; // stores the current access time of a certain operation
	int userType; // 1 - customer, 2 - manager, 3 - maintenance
	User(int); // normal user constructor
	User(int, int); // special user constructor for session restoration
	void printTrace(); // print out the operations that a given user has performed in his/her session
	static User* getUser (int); // returns the user object pointer from a given userID
	static string currentTime(); // function to display and record the current time, used in conjunction with other operations for execution tracing
	static void userDetailsAll(); // displays the account information of all users
	static void userInfo(int); // displays the account information of a specified user
	static void createDummyUsers(); // create various number of dummy users, only by the manager
	static void exportUserTrace(int, int); // export the current session user details to a text file
	static void addUserTrace(int, string); // add user trace to a specific user
	static void addExecTrace(int, string); // add execution trace to a specific user
	static void getStats(); // gets some basic statistics of the bank accounts in the bank
	static void writeToFile(User); // writes the user/account information to a textfile
};

#endif /* USER_H_ */
