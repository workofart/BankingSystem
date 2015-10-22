/*
 * main.cpp
 *
 *  Created on: Sep 26, 2015
 *      Author: Hanxiang Pan
 *      StudentNumber: 250608428
 */

#include "main.h"

void switchExecTrace(); // prototype of static function
void executeOptions(int, int);
void saveToFile();
void restore();

/**
 * switchExecTrace method switches the execution trace from "ON" to "OFF" or vice versa
 */
void main::switchExecTrace() {
	cout << "Switched from " + to_string(User::execTraceBool) + " to ";
	User::execTraceBool = !User::execTraceBool;
	cout << to_string(User::execTraceBool) << endl;
} // end switchExecTrace method

/**
 * saveToFile method saves the vector of users/accounts into a text file for future restoration
 */
void main::saveToFile(){
	ofstream outputfile;
	outputfile.open("usersession.txt");
	for (auto &i : User::userVec){
		outputfile << i.userID << '\n';
		outputfile << i.userType << '\n';
	} // end for loop
	outputfile.close();

	outputfile.open("accountsession.txt");
	for (auto &i : Account::accountVec){
		outputfile << i.userID << '\n';
		outputfile << i.accType << '\n';
		outputfile << i.balance << '\n';
	} // end for loop
	outputfile.close();
} // end saveToFile method

/**
 * restore method restores the user and account vectors based on the saved file
 */
void main::restore(){
	/************* User session restore ***************/
	ifstream inUserFile("usersession.txt");
	int userID = -999, userType = -999;
	string line;
	while (getline(inUserFile, line))
	{
		std::istringstream iss(line);
		userID = stoi(line);
		getline(inUserFile, line);
		userType = stoi(line);
		User::userVec.push_back(User::User(userID, userType)); // initialize the created objects as "Customer" type

	}

	if (userID == -999 && userType == -999) User::createDummyUsers(); // invoke createDummyUsers method if no session was restored
	if (userID != -999 || userType != -999) cout << "User session restored" << endl;
	inUserFile.close();

	/************* Account session restore ***************/
	ifstream inAccountFile("accountsession.txt");
	userID = -999;
	int accType = -999;
	double balance = -999;

	while (getline(inAccountFile, line))
	{

		std::istringstream iss(line);
		userID = stoi(line);
		getline(inAccountFile, line);
		accType = stoi(line);
		getline(inAccountFile, line);
		balance = stod(line);
		Account::accountVec.push_back(Account::Account(userID, accType)); // initialize the created objects as "Customer" type
		Account::addBalance(Account::getAcc(userID, accType), balance); // restore the balance of a particular account

	}

	if (userID != -999 || accType != -999 || balance != -999) cout << "Account session restored" << endl;
	inAccountFile.close();
} // end restore method

/**
 * executeOptions method will match the command the user entered with the corresponding functions
 * A check is performed on the input option for to see if it's a valid command
 * Adjustments will be made to the commands for organizational purposes
 */
void main::executeOptions(int userID, int option) {
	int actualOption = 0;
	int uid = 0;
	int tempOption = 0;
	double tempAmount = 0;
	// customer
	if (userID > 0) {
		if (option >= 1 && option <= 6) {
			actualOption = option; // no adjustments needed
		}
	}
	// manager
	else if (userID == -1) {
		if (option >= 1 && option <= 6) {
			actualOption = option + 6; // adjust for the previous type of user
		}

		else {cout << "Invalid user ID or option...exiting"; cout << "here 1" << endl; return;}
	}
	// maintenance
	else if (userID == -2) {
		if (option == 1 || option == 2) {
			actualOption = option + 12; // adjust for the previous two types of users
		}
		else {cout << "Invalid user ID or option...exiting"; cout << "here 2" << endl; return;}
	}
	// invalid userID
	else {cout << "Invalid user ID or option...exiting"; cout << "here 3" << endl; return;}

	/**
	 * Options Branching:
	 * 1. Check balance
	 * 2. Withdrawal
	 * 3. Deposit
	 * 4. Transfer Funds (within user)
	 * 5. E-transfer (across users)
	 * 6. Logout
	 * 7. Open Bank Account
	 * 8. Close Bank Account
	 * 9. Print out all customers' info
	 * 10. Print out specific customer info
	 * 11. Get stats
	 * 12. Logout
	 * 13. Switch Execution Trace
	 * 14. Logout
	 */
	switch (actualOption) {
	case 1:
		User::addExecTrace(userID, "checkBalance() invoked");
		Account::checkBalance(userID);
		User::addExecTrace(userID, "checkBalance() returned");
		User::addUserTrace(userID, "Checked balance");
		break;
	case 2:
		User::addExecTrace(userID, "withdrawal(" + to_string(userID) + ") invoked");
		Account::withdrawal(userID); // user trace within the function
		User::addExecTrace(userID, "withdrawal(" + to_string(userID) + ") returned");
		break;
	case 3:
		User::addExecTrace(userID, "deposit(" + to_string(userID) + ") invoked");
		Account::deposit(userID); // user trace within the function
		User::addExecTrace(userID, "deposit(" + to_string(userID) + ") returned");
		break;
	case 4:
		User::addExecTrace(userID, "transfer(" + to_string(userID) + ") invoked");
		Account::transfer(userID); // user trace within the function
		User::addExecTrace(userID, "transfer(" + to_string(userID) + ") returned");
		break;
	case 5:
		cout << "Please enter the destination UserID:" << endl;
		cout << ">>";
		cin >> uid;
		User::addExecTrace(userID, "e-transfer(" + to_string(userID) + ", " + to_string(uid) + ") invoked");
		Account::e_transfer(userID, uid);
		User::addExecTrace(userID, "e-transfer(" + to_string(userID) + ", " + to_string(uid) + ") returned");
		break;
	case 7:
		User::addExecTrace(userID, "openAccount() invoked");
		Account::openAccount(); // user trace within the function
		User::addExecTrace(userID, "openAccount() returned");
		break;
	case 8:
		cout << "Closing Bank Account" << endl;
		User::addExecTrace(userID, "closeAccount() invoked");
		Account::closeAccount();
		User::addExecTrace(userID, "closeAccount() returned");
		break;
	case 9:
		User::addExecTrace(userID, "userDetailsAll() invoked");
		User::userDetailsAll();
		User::addExecTrace(userID, "userDetailsAll() returned");
		break;
	case 10:
		cout << "Please enter the user ID for the user info" << endl;
		cout << ">>";
		cin >> uid;
		User::addExecTrace(userID, "userInfo(" + to_string(uid) + ") invoked");
		User::userInfo(uid);
		User::addExecTrace(userID, "userInfo(" + to_string(uid) + ") returned");
		break;
	case 11:
		cout << "Printing stats of the current bank accounts" << endl;
		User::addExecTrace(userID, "getStats() invoked");
		User::getStats();
		User::addExecTrace(userID, "getStats() returned");
		break;
	case 13:
		cout << "Switching Execution Trace" << endl;
		User::addExecTrace(userID, "switchExecTrace() invoked");
		main::switchExecTrace();
		User::addExecTrace(userID, "switchExecTrace() returned");
		break;
		// Logout is same for all 3 types of users
	case 6:
	case 12:
	case 14:
		cout << "Logging out..." << endl;
		cout << User::getUser(userID)->userTrace;
		cout << "=================================================================" << endl;
		cout << "Export session receipt? Yes (1), No (0)" << endl;
		cin >> actualOption;
		User::addExecTrace(userID, "exportUserTrace(" + to_string(actualOption) + ", " + to_string(userID) + ") invoked");
		User::exportUserTrace(actualOption, userID);
		User::addExecTrace(userID, "exportUserTrace(" + to_string(actualOption) + ", " + to_string(userID) + ") returned");
		User::getUser(userID)->userTrace = ""; // erase session user trace
		break;
	default:
		cout << "Invalid user ID or option...exiting";
		break;
	} // end switch statement
	return;
} // end executeOptions method

/**
 * Main method
 */
int main () {
	int userID = -5;
	int n = 0; // for any temp quantity input
	int input;
	main::restore(); // restore the session file
	cout << "\t\t\t\tWelcome to Hanxiang (Henry)'s Bank" << endl;
	cout << "======================================================================================" << endl;
	while (userID > User::userVec.size()-2 || userID < 0 || !isdigit(userID)){ // accomodate that a manager user and maintenance user has been created

		cout << "Please enter your userID to login first (enter -999 to exit):" << endl;
		cout << ">>";
		cin >> userID;
		if (userID == -999) { cout << "Quitting program..."; main::saveToFile(); return 0;}
		if (userID < User::userVec.size()-2 && userID > 0 && isdigit(userID)) {cout << string("=================== Welcome UID: ") + to_string(userID) + " ===================" << endl;}
		Account::accountStatus(userID);
		loop:
		// the user is a normal customer
		// accomodate that a manager user and maintenance user has been created
		if (userID <= User::userVec.size()-2 && userID > 0) {
			cout << "======================================================" << endl;
			cout << "Please enter the operation you would like to perform: " << endl;
			cout << "||                1. Check balance                  ||" << endl;
			cout << "||                2. Withdrawal                     ||" << endl;
			cout << "||                3. Deposit                        ||" << endl;
			cout << "||                4. Transfer Funds                 ||" << endl;
			cout << "||                5. E-transfer (across users)      ||" << endl;
			cout << "||                6. Logout                         ||" << endl;
			cout << "======================================================" << endl;
		}
		// Manager Login
		else if (userID == -1) {
			cout << "======================================================" << endl;
			cout << "Please enter the operation you would like to perform: " << endl;
			cout << "||               1. Open Bank Account                 " << endl;
			cout << "||               2. Close Bank Account                " << endl;
			cout << "||               3. Print out all customers' info     " << endl;
			cout << "||               4. Print out specific customer info  " << endl;
			cout << "||               5. Get Bank Stats                    " << endl;
			cout << "||               6. Logout                            " << endl;
			cout << "======================================================" << endl;
		}
		// Maintenance Login
		else if (userID == -2) {
			cout << "======================================================" << endl;
			cout << "Please enter the operation you would like to perform: " << endl;
			cout << "||               1. Switch Execution Trace            " << endl;
			cout << "||               2. Logout                            " << endl;
			cout << "======================================================" << endl;
		}
		else {
			cin.clear(); // clear the failed state caused by a non-integer input
			cin.ignore(100, '\n');
			cout << "invalid userID, please try again" << endl;
			continue;
		}
		cout << ">>";
		cin >> input;
		main::executeOptions(userID, input);
		if ((input == 2 && userID == -2) || (userID == -1 && input == 6) || (userID > 0 && input == 6)) {
			userID = -5;
			continue;
		}
		else {
			goto loop;
		}
	} // end while loop
	return 0;
}; // end main method
