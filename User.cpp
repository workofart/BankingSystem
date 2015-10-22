/*
 * User.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: Hanxiang Pan
 *      StudentNumber: 250608428
 */

#include "User.h"
std::vector<User> User::userVec; // redefine the static variable and initialize
int User::uidCounter = 1; // redefine the static variable and initialize
bool User::execTraceBool = false; // redefine the static variable and initialize
void addUserTrace(int, string);
void addExecTrace(int, string);
void exportUserTrace(int, int);
void getStats();
void writeToFile(User);

User::User(int userType) {
	User::uidCounter++; // increment global counter
	User::userType = userType; // 1 - customer, 2 - manager, 3 - maintenance
	User::userTrace = "===============Operations performed in the session==============\n";
//	User::execTraceBool = false;
	User::execTrace = "===============Execution Trace ==============\n";
}

// constructor for special users/session restore
User::User(int password, int userType){
	User::userID = password; // -1 manager, -2 maintenance
	User::userType = userType; // 1 - customer, 2 - manager, 3 - maintenance
	User::userTrace = "===============Operations performed in the session==============\n";
//	User::execTraceBool = false;
	User::execTrace = "===============Execution Trace ==============\n";
}

/**
 * Create n dummy customer users in the system
 */
void User::createDummyUsers(){

	int n;
	cout << "Please enter the number of dummy users to create\n>>";
	cin >> n;
	cout << "Start creating " << n << " dummy users" << endl;
	cout << "..." << endl;
	for (int i = 1; i<= n; i++){
		User::userVec.push_back(User::User(1)); // initialize the created objects as "Customer" type
		usleep(50000); // delay for emulation
		cout << "Created user #" <<i << endl;
	}
	User::userVec.push_back(User::User(-1,2)); // create manager
	User::userVec.push_back(User::User(-2,3)); // create maintenance guy
	cout << ">>Done creating " << n << " dummy users" << endl;
}

/**
 * Retrieves the bank account with the specified userID and account type
 */
User* User::getUser (int userID){
	User temp = User (-999);
	if (User::userVec.size() == 0){
		cout << "There are no users in the system" << endl;
		return &temp;
	}
	else {
		for (auto &i : User::userVec){
			if (i.userID == userID){
				return &i;
			}
		} // end for loop
		cout << "No user with the userID " << userID << " found" << endl;
		return &temp;
	} // end else
} // end getUser method

/**
 * currentTime method returns the current time (year, month, date, hour, minute)
 */
string User::currentTime () {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	string accessTime;
	accessTime = to_string(now->tm_year + 1900) + '-' + to_string(now->tm_mon + 1) + '-'
			+ to_string(now->tm_mday) + " " + to_string(now->tm_hour) + ":" + to_string(now->tm_min);

	return accessTime;
} // end currentTime method

/**
 * userDetailsAll method will print out all the user's bank account info
 * Balance
 *
 */
void User::userDetailsAll(){
	cout << "Printing all customers' info" << endl;
	cout << "===================" << endl;
	for (auto &i : User::userVec){
		i.userInfo(i.userID);
		cout << "===================" << endl;
	}
} // end userDetailsAll method

/**
 * userInfo method takes the userID and displays the balance of each account if it exists
 */
void User::userInfo(int userID){
	cout << "UserID " << userID << "'s info" << endl;
	if (Account::getAcc(userID,1)->accType == -999){
		cout << "No chequing account found" << endl;
	}
	if (Account::getAcc(userID,2)->accType == -999){
		cout << "No savings account found" << endl;
	}
	if (Account::getAcc(userID,1)->accType != -999){
		cout << "Chequing account $" << Account::getAcc(userID, 1)->balance << endl;
	}
	if (Account::getAcc(userID,2)->accType != -999){
		cout << "Savings account $" << Account::getAcc(userID, 2)->balance << endl;
	}
	else
		return;
} // end userDetailsAll method

/**
 * addUserTrace method adds the operations that a certain user performed within
 * its session and add it to the userTrace string
 */
void User::addUserTrace(int userID, string s){
	User::getUser(userID)->userTrace += User::currentTime() + "  "+ s + "\n";
} // end addUserTrace method

/**
 * exportUserTrace method exports the session log of a particular user to a text file
 */
void User::exportUserTrace(int option, int userID){
	if (option == 0) return;
	ofstream outputfile;
	outputfile.open(string("Receipt_") + "UID" + to_string(userID) + ".txt");
	outputfile << User::getUser(userID)->userTrace << endl;
	outputfile.close();
} // end exportUserTrace method

/**
 * addExecTrace method adds the functions invocation and return status to each
 * user's execution trace log based on the execution trace triggered by the maintenance person
 */
void User::addExecTrace(int userID, string s){
	// verify if the user trace is switched on

	if (User::execTraceBool == true){
		// continue
		User::getUser(userID)->execTrace+= User::currentTime() + "  " + s + "\n";
		ofstream outputfile;
		outputfile.open("UID" + to_string(userID) + "trace.txt");
		outputfile << User::getUser(userID)->execTrace << endl;
		outputfile.close();
	}
	else
		return; // exit
} // end addExecTrace method

/**
 * getStats method will print out some basic statistics about the accounts in the bank system
 */
void User::getStats(){
	double sum = 0, mean = 0, max = 0, min = 0;
	int counter = 0;

	for (auto &i : Account::accountVec){
		sum += i.balance;
		counter++;
		if (i.balance > max) max = i.balance; // replace with the new max balance
		else if (i.balance < min) min = i.balance; // replace with the new min balance
		else; // do nothing
	} // end for loop
	mean = sum / counter;
	cout << "==================" << endl;
	cout << "Average Balance \t Max Balance \t Min Balance" << endl;
	cout << round(mean * 10) / 10 << "\t\t\t" << round(max * 10) / 10 << "\t\t" << round(min * 10) / 10 << endl;
} // end getStats method
