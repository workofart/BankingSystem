/*
 * Account.h
 *
 *  Created on: Sep 30, 2015
 *      Author: Hanxiang Pan
 *      StudentNumber: 250608428
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "User.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <vector>
#include <stack>
#include <algorithm>

class User; // forward declaration

using namespace std;

class Account{
public:
	Account(int, int); // Account constructor
	int userID; // keep consistent with the static counter
	int accType; // Chequing - 0, Savings - 1
	static vector<Account> accountVec; // a vector that stores all the accounts created
	double balance; // the balance of a given bank account (chequing or savings)
	static void openAccount (); // function to create an account
	static void closeAccount(); // function to close an account
	static void withdrawal(int); // function to draw a given amount of money from the account
	static void deposit(int); // function to deposit a given amount of moeny to the specified account
	static void checkBalance(int); // check the balance of the specified user
	static void transfer(int); // transfer funds from one account to another
	static Account* getAcc (int, int); // retrieves the account for a given user
	static void addBalance(Account*,double); // add a value (positive/negative) to the current balance of an account
	static void e_transfer(int, int); // transfer funds across users
	static void accountStatus (int userID); // displays the account status (exist or not)
};

#endif /* ACCOUNT_H_ */
