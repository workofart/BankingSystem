/*
 * Account.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: Hanxiang Pan
 *      StudentNumber: 250608428
 */

#include "Account.h"
//double Account::balance; // redefine static variable
std::vector<Account> Account::accountVec; // redefine the static variable
void closeAccount(int, int);
void e_transfer(int, int);
void accountStatus (int);

/**
 * Account constructor that intializes the userID, accType and balance of 0
 */
Account::Account(int userID, int accType) {
	Account::userID = userID;
	Account::accType = accType;
	Account::balance = 0;
}

/**
 * openAccount method prompts the manager to open chequing or savings accounts for a specified user
 */
void Account::openAccount() {
	int accType = 0, userID = 0;
	cout << "Opening Bank Account" << endl;
	cout << "Which type of account would you like to open? Chequing (1) Savings (2)" << endl;
	/****************** Account Type Check *****************/
	while (accType != 1 || accType != 2) {
		cout << ">>";
		cin >> accType;
		cout << "What is the associated userID for the account?" << endl;
		cout << ">>";
		cin >> userID;
		/******************* UserID Check ****************/
		// Either the userID exceeds the size of the user vector or is less than 0
		while (userID > User::userVec.size() || userID < 0 || User::getUser(userID)->userType == -999) {
			cout << "please re-enter the userID" << endl;
			cout << ">>";
			cin >> userID;
		}
		// Chequing account
		if (accType == 1) {
			cout << "An chequing account has been created for userID: " << userID << endl;
			Account* newAcc = new Account(userID, accType); // create a new Account object using the constructor
			Account::accountVec.push_back(*newAcc); // store the newly created account in the account vector
			User::addUserTrace(-1, "Opened a chequing account for userID: " + to_string(userID));
			return;
		}
		// Savings account
		else if (accType == 2) {
			cout << "An savings account has been created for userID: " << userID << endl;
			Account* newAcc = new Account(userID, accType); // create a new Account object using the constructor
			Account::accountVec.push_back(*newAcc); // store the newly created account in the account vector
			User::addUserTrace(-1, "Opened a savings account for userID: " + to_string(userID));
			return;
		}
		else {
			cout << "Invalid option, please try again" << endl;
		}
	} // end while
} // end openAccount method

/**
 * withdrawal method withdraws money from a given user and a given account.
 * Has checks for below $1000 threshold and alerts the client for a $2 fee
 */
void Account::withdrawal(int userID) {
	int temp = 0;
	int tempOption = 0, tempAmount = 0;

	cout << "Withdrawing" << endl;
	cout << "Which account chequing (1) or savings (2) would you like to withdraw from?" << endl;

	/****************** Option Check *****************/
	while (tempOption != 1 || tempOption != 2) {
		cout << ">>";
		cin >> tempOption;
		cout << "How much to withdraw?" << endl;
		cout << ">>";
		cin >> tempAmount;
		/******************* Amount Check ****************/
		while (tempAmount < 0) {
			cout << "please re-enter the amount" << endl;
			cout << ">>";
			cin >> tempAmount;
		}
		Account *tempAcc1 = Account::getAcc(userID, tempOption);
		// check if account exists
		if (tempAcc1->userID == -999) {
			cout << "That account doesn't exist" << endl;
			return;
		}
		/**************** Chequing Account ****************/
		if (tempOption == 1) {
			// check if the user has sufficient balance for the amount
			while (tempAcc1->balance < tempAmount) {
				cout << "Insufficient balance, $" << tempAcc1->balance << " left in account" << endl;
				cout << "Please try a different amount" << endl;
				cout << ">>";
				cin >> tempAmount;
			} // end while - check for sufficient balance

			// Alert for balance lower than $1000
			if (tempAcc1->balance - tempAmount < 1000) {
				cout << "Your balance will be below $1000, continuing withdrawal will result in a $2 fee per transaction" << endl;
				cout << "Continue? Yes(1), No(2)" << endl;
				cout << ">>";
				cin >> temp;
				if (temp == 1) {
					Account::addBalance(tempAcc1, -(tempAmount+2));
					//					tempAcc1->balance -= (tempAmount + 2);
					cout << "Withdrew $" << tempAmount + 2 << " from your chequing account (including transaction fee)" << endl;
					User::addUserTrace(userID, "Withdrew $" + to_string(tempAmount + 2) + " from your chequing account (including transaction fee)");
					cout << "Your balance is $" << tempAcc1->balance << endl;
					return;
				}
				else
					return;
			} // end if condition - balance lower than $1000

			// No transaction fee or alert
			else {
				Account::addBalance(tempAcc1, -tempAmount);
				cout << "Withdrew $" << tempAmount << " from your chequing account" << endl;
				User::addUserTrace(userID, "Withdrew $" + to_string(tempAmount) + " from your chequing account");
				cout << "Your balance is $" << tempAcc1->balance << endl;
				return;
			}
		} // end if condition - option 1 chequing account

		/**************** Savings Account ****************/
		else if (tempOption == 2) {

			// check if the user has sufficient balance for the amount
			while (tempAcc1->balance < tempAmount) {
				cout << "Insufficient balance, $" << tempAcc1->balance << " left in account" << endl;
				cout << "Please try a different amount" << endl;
				cout << ">>";
				cin >> tempAmount;
			} // end while - check sufficient balance

			// Alert for balance lower than $1000
			if (tempAcc1->balance - tempAmount < 1000) {
				cout << "Your balance will be below $1000, continuing withdrawal will result in a $2 fee per transaction" << endl;
				cout << "Continue? Yes(1), No(2)" << endl;
				cout << ">>";
				cin >> temp;
				if (temp == 1) {
					Account::addBalance(tempAcc1, -(tempAmount+2));
					cout << "Withdrew $" << tempAmount + 2 << " from your savings account (including transaction fee)" << endl;
					User::addUserTrace(userID, "Withdrew $" + to_string(tempAmount + 2) + " from your savings account (including transaction fee)");
					cout << "Your balance is $" << tempAcc1->balance << endl;
					return;
				}
				else
					return;
			} // end if condition - balance lower than $1000

			// No transaction fee or alert
			else {
				Account::addBalance(tempAcc1, -tempAmount);
				cout << "Withdrew $" << tempAmount << " from your savings account" << endl;
				User::addUserTrace(userID, "Withdrew $" + to_string(tempAmount) + " from your savings account");
				cout << "Your balance is $" << tempAcc1->balance << endl;
				return;
			}
		} // end if condition - savings account
		else {
			cout << "Invalid option, please try again" << endl;
		}
	} // end while
} // end withdrawal method

/**
 * Deposit money to a given account
 */
void Account::deposit(int userID) {
	int tempOption = 0;
	double tempAmount = 0;
	cout << "Depositing to user:" << userID << endl;
	cout << "Which account chequing (1) or savings (2) would you like to deposit to?" << endl;
	/****************** Option Check *****************/
	while (tempOption != 1 || tempOption != 2) {
		cout << ">>";
		cin >> tempOption;
		cout << "How much to deposit?" << endl;
		cout << ">>";
		cin >> tempAmount;
		/******************* Amount Check ****************/
		while (tempAmount <= 0) {
			cout << "please re-enter the amount" << endl;
			cout << ">>";
			cin >> tempAmount;
		}
		Account *tempAcc1 = Account::getAcc(userID, tempOption);
		// check if account exists
		if (tempAcc1->userID == -999){
			cout << "That account doesn't exist" << endl;
			return;
		}
		else if (tempOption == 1) {
			cout << "Deposited $" << tempAmount << " to your chequing account" << endl;
			Account::addBalance(tempAcc1, tempAmount);
			User::addUserTrace(userID, "Deposited $" + to_string(tempAmount) + " to your chequing account");
			cout << "Your balance is $" << tempAcc1->balance << endl;
			return;
		}
		else if (tempOption == 2) {
			cout << "Deposited $" << tempAmount << " to your savings account" << endl;
			Account::addBalance(tempAcc1, tempAmount);
			//			tempAcc1->balance += tempAmount;
			//			Account::balance += tempAmount;
			User::addUserTrace(userID, "Deposited $" + to_string(tempAmount) + " to your savings account");
			cout << "Your balance is $" << tempAcc1->balance << endl;
			return;
		}
		else {
			cout << "Invalid option, please try again" << endl;
		}
	} // end while
} // end deposit method

/**
 * closeAccount method prompts the manager to close a specified user's specified account
 */
void Account::closeAccount() {
	int userID= 0, accType = 0;
	cout << "Which userID is the account associated with?" << endl;
	cout << ">>";
	cin >> userID;
	cout << "Which account chequing (1) or savings (2) would you like to close?" << endl;
	cout << ">>";
	cin >> accType;

	// Iterator for finding the right account to close
	for(std::vector<Account>::iterator iter = Account::accountVec.begin(); iter != Account::accountVec.end(); ++iter ) {
		if( &*iter ==  Account::getAcc(userID, accType)) {
			// check if balance is 0
			if (Account::getAcc(userID, accType)->balance == 0){
				Account::accountVec.erase(*&iter);
				cout << "Account removed!" << endl;
				Account::getAcc(userID, accType);
				if (accType == 1) User::addUserTrace(-1, "Removed chequing account for userID: " + to_string(userID));
				if (accType == 2) User::addUserTrace(-1, "Removed savings account for userID: " + to_string(userID));
				break;
			}
			// will not close account if balance is greater than 0, prompts the manager
			else {
				cout << "Balance greater than 0... close account denied, please transfer out all funds before closing the account" << endl;
				break;
			}
		} // end if statement - check if account exists
		else
			cout << "The account with the associated userID was not found" << endl;
	} // end for loop - iterate through the accounts vector
} // end closeAccount method

/**
 * transfer method transfers funds within a user's accounts (savings to chequing or vice versa)
 */
void Account::transfer (int userID) {
	int tempAmount = 0, tempOption = 0;
	cout << "Transferring Funds" << endl;
	cout << "Which account chequing (1) or savings (2) would you like to transfer *OUT* of?" << endl;

	/****************** Account Type Check *****************/
	while (tempOption != 1 || tempOption != 2) {
		cout << ">>";
		cin >> tempOption;
		cout << "How much to transfer?" << endl;
		cout << ">>";
		cin >> tempAmount;
		Account *tempAcc1 = Account::getAcc(userID, tempOption);
		if (tempAcc1->accType == -999){ cout << "That account doesn't exist" << endl; return;}

		/******************* Amount Check ****************/
		while (tempAmount < 0 || tempAmount > tempAcc1->balance) {
			cout << "Invalid amount, please re-enter the amount" << endl;
			cout << ">>";
			cin >> tempAmount;
		}
		// chequing to savings
		if (tempOption == 1) {
			cout << "Transferred $" << tempAmount << " from your chequing account to your savings account" << endl;
			Account::addBalance(tempAcc1, -tempAmount);
			Account::addBalance(getAcc(userID,2), tempAmount);
			User::addUserTrace(userID, "Transferred $" + to_string(tempAmount) + " from your chequing account to your savings account");
			return;
		}
		// savings to chequing
		else if (tempOption == 2) {
			cout << "Transferred $" << tempAmount << " from your savings account to your chequings account" << endl;
			Account::addBalance(tempAcc1, -tempAmount);
			Account::addBalance(getAcc(userID,1), tempAmount);
			User::addUserTrace(userID, "Transferred $" + to_string(tempAmount) + " from your savings account to your chequing account");
			return;
		}
		else {
			cout << "Invalid option, please try again" << endl;
		}
	} // end while
} // end transfer method

/**
 * e_transfer method transfers fund across accounts for 2 different users
 */
void Account::e_transfer (int uidFrom, int uidTo) {
	int tempAmount = 0, tempOption = 0, tempOption2 = 0;
	cout << "Transferring Funds" << endl;
	//	User *tempUserFrom = User::getUser(uidFrom);
	//	User *tempUserTo = User::getUser(uidTo);

	/****************** Account Type Check *****************/
	while (tempOption != 1 || tempOption != 2) {
		cout << "Which account chequing (1) or savings (2) would you like to transfer *FROM*?" << endl;
		cout << ">>";
		cin >> tempOption;
		cout << "Which account chequing (1) or savings (2) would you like to transfer *TO*?" << endl;
		cout << ">>";
		cin >> tempOption2;
		// check valid account type input
		if ((tempOption != 1 && tempOption != 2) || (tempOption2 != 1 && tempOption2 != 2)){
			cout << "Invalid option, please try again" << endl;
			continue;
		}
		cout << "How much to transfer?" << endl;
		cout << ">>";
		cin >> tempAmount;
		Account *tempAcc1 = Account::getAcc(uidFrom, tempOption);
		Account *tempAcc2 = Account::getAcc(uidTo, tempOption2);
		if (cin.fail()) {cin.clear(); cin.ignore(100, '\n');} // detect non-integer input failure and recover

		/******************* Amount Check ****************/
		while (tempAmount < 0 || tempAmount > tempAcc1->balance) {
			cout << "Invalid amount, please re-enter the amount" << endl;
			cout << ">>";
			cin >> tempAmount;
		}
		// check if the two accounts actually exists
		if (tempAcc1->accType == -999 || tempAcc2->accType == -999) { cout << "One of the accounts doesn't exist" << endl; return;}
		Account::addBalance(tempAcc1, -tempAmount);
		Account::addBalance(tempAcc2, tempAmount);
		User::addUserTrace(uidFrom, string("UID") + to_string(uidFrom) + " transferred $" + to_string(tempAmount) + " to UID" + to_string(uidTo));
		return;
	} // end while loop
} // end transfer method



/**
 * getAcc method retrieves the bank account with the specified userID and account type
 */
Account* Account::getAcc (int userID, int accType) {
	User::addExecTrace(userID, "getAcc(" + to_string(userID) + ", " + to_string(accType) + ") invoked");
	Account temp = Account (-999,-999);

	// check if there is any accounts at all
	if (Account::accountVec.size() == 0) {
		User::addExecTrace(userID, "getAcc(" + to_string(userID) + ", " + to_string(accType) + ") returned");
		return &temp;
	}
	// there are accounts in the system, find the right one
	else {
		for (auto &i : Account::accountVec) {

			if (i.userID == userID && i.accType == accType) {
				User::addExecTrace(userID, "getAcc(" + to_string(userID) + ", " + to_string(accType) + ") returned");
				return &i;
			}
			else {
			}
		}
		User::addExecTrace(userID, "getAcc(" + to_string(userID) + ", " + to_string(accType) + ") returned");
		return &temp;
	} // end else - searching for account
} // end getAcc method

/**
 * checkBalance method returns the balance of a given user/account
 */
void Account::checkBalance(int userID) {
	int tempOption = -999;
	cout << "Checking balance" << endl;
	cout << "Which account chequing (1) or savings (2) would you like to check?" << endl;

	/************** Account Type Check ***************/
	while (tempOption != 1 || tempOption != 2) {
		cout << ">>";
		cin >> tempOption;
		Account *tempAcc1 = Account::getAcc(userID, tempOption);
		// check if the account actually exists
		if (tempAcc1->userID == -999 && tempAcc1->accType == -999) {
			cout << "The acccount doesn't exist." << endl;
			return;
		}
		// chequing account
		if (tempOption == 1) {
			cout << "Your chequing balance is $" <<  round(tempAcc1->balance * 10) / 10 << endl;
			return;
		}
		// savings account
		else if (tempOption == 2) {
			cout << "Your savings balance is $" << round(tempAcc1->balance * 10) / 10 << endl;
			return;
		}
		else {
			cout << "Invalid option, please try again" << endl; // invalid account type, retry
		}
	} // end option check while
} // end checkBalance method that checks the specified balance of a given user

/**
 * accountStatus method displays which account(s) the specified user has/have currently and displays the status
 */
void Account::accountStatus (int userID){
	// chequing account exists
	if (Account::getAcc(userID, 1)->accType != -999) {
		cout << "Chequing account exists" << endl;
	}
	// savings account exists
	if (Account::getAcc(userID, 2)->accType != -999) {
		cout << "Savings account exists" << endl;
	}
	// chequing account doesn't exist
	if (Account::getAcc(userID, 1)->accType == -999) {
		cout << "Chequing account doesn't exist" << endl;
	}
	// savings account doesn't exist
	if (Account::getAcc(userID, 2)->accType == -999) {
		cout << "Savings account doesn't exist" << endl;
	}
} // end accountStatus method

/**
 * addBalance method is the utility method for withdrawing/depositing funds for a given account
 */
void Account::addBalance (Account *acc, double amount){
	User::addExecTrace(acc->userID, string("addBalance(") + "*acc, " + to_string(amount) + ") invoked");
	acc->balance += amount;
	User::addExecTrace(acc->userID, string("addBalance(") + "*acc, " + to_string(amount) + ") returned");
} // end addBalance method
