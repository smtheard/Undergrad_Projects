//MenuView.cpp programming assignment 3
//cpp file for programming assignment 3
//Stefan Theard
//6/25/2013
#include <iostream>
#include "MenuView.h"

using namespace std;

int MenuView::userChoiceMenu()
{

	cout << "Are you a customer, employee, or do you want to print info?" << endl
	     << "1. Bank Customer " << endl
		 << "2. Bank Employee " << endl
		 << "3. Print " << endl
		 << "9. Exit " << endl;
	cin >> userChoice;
	return userChoice;
}

int MenuView::customerMenu()
{
	cout << "Customer Options: " << endl
		 << "1. Write a Check " << endl
		 << "2. Withdraw from Checking Account " << endl
		 << "3. Withdraw from Savings Account "<< endl
		 << "4. Deposit to Checking Account " << endl
		 << "5. Deposit to Savings Account " << endl;
	cin >> userChoice;
	return userChoice;
}

int MenuView::bankEmployeeMenu()
{
	cout << "Employee Options: " << endl
		 << "1. Create Checking Account " << endl
		 << "2. Create Savings Account " << endl
		 << "3. Post Interest on an Account "<<endl;
	cin >> userChoice;
	return userChoice;
}

void MenuView::getCheckInfo(string& customerName, int& acntNumber, double& depositAmt)
{
	cout <<"Enter your name: ";
	cin >> customerName;
	cout << "Enter your account number: ";
	cin >> acntNumber;
	cout << "Enter your check amount: ";
	cin >> depositAmt;
}

void MenuView::getWithdrawInfo(string& customerName, int& acntNumber, double& amount)
{
	cout <<"Enter your name: ";
	cin >> customerName;
	cout << "Enter your account number: ";
	cin >> acntNumber;
	cout << "Enter your withdraw amount: ";
	cin >> amount;
}

void MenuView::getDepositInfo(int& acntNumber, double& amount)
{
	cout << "Enter your account number: ";
	cin >> acntNumber;
	cout << "Enter your deposit amount: ";
	cin >> amount;
}

void MenuView::getCustomerInfo(string& customerName, int& acntNumber, double& amount)
{
	cout <<"Enter customer name: ";
	cin >> customerName;
	cout << "Enter account number for customer: ";
	cin >> acntNumber;
	cout << "Enter customers initial deposit amount: ";
	cin >> amount;
}

void MenuView::getAccountNumInfo(int& acntNumber)
{
	cout << "Enter account number: ";
	cin >> acntNumber;
}

void MenuView::accountNotFound()
{
	cout << "Account not found!" << endl;
}


