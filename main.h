/*
 * main.h
 *
 *  Created on: Sep 26, 2015
 *      Author: Hanxiang Pan
 *      StudentNumber: 250608428
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "User.h"
#include "Account.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <vector>
#include <stack>
#include <fstream>
#include <cctype>
#include <string>  // for reading lines
#include <sstream> // for reading lines

class User; // forward declaration
class Account; // forward declaration

using namespace std;

class main {
public:
	main(); // main method
	static void executeOptions(int, int); // the utility function that branches out to the desired functions
	static void switchExecTrace(); // switch on/off execution trace
	static void saveToFile(); // saves account/user information to a file for restoration
	static void restore(); // restores the account/users from a file
};

#endif /* MAIN_H_ */
