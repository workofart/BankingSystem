# BankingSystem

The banking system is a simple C++ program that has 3 types of users that exist in a typical banking system: customer, manager, maintenance person

This application was developed for an object oriented design course at Western. 

At the start of the program, it will prompt the user to enter how many dummy users to create (Normal users).

*Each user has its own defined actions:*

**Client (Normal User)**

* Check balance (savings or chequing)
* Withdraw funds (with $1000 threshold check and warning, insufficient fund warning, and $2 fee for insufficient fund withdrawal)
* Deposit funds
* Transfer funds (savings to chequing or vice versa)
* E-transfer (across users)
* After login, displays which accounts exists so the user can perform suitable operations

**Manager (UserID = -1)**

* Open bank account (savings or/and chequing) for a specified user
* Close bank account (restricts closing only if balance = 0)
* Print all customer account info formatted(UserID, AccountType, Balance)
* Print specific customer account info formatted (AccountType, Balance)
* Get bank account statistics (max, min, mean funds)

**Maintenance Person (UserID = -2)**

* Switch ON or OFF execution trace

**General Features (For all users)**

* Saves the session accounts/users in a text file, and allows for the session to be restored later* Receipt display after logout with option to export receipt


# Install
**Tested Platform : Mac OSX ****Other Requirements: C++11 extension**
To install, simply pull the master branch to download the application. Then, use the command to build and compile:
    g++ -w main.cpp Account.cpp User.cpp -o output


# Run

After the program is compiled, use the command to run:
    ./output


# Documentation
The entire program is documented in Javadoc format embedded in the java files