//BankAccount.cpp programming assignment 3
//cpp file for programming assignment 3
//Stefan Theard
//6/25/2013
#include <iostream>
#include <cstdlib>

#include "BankAccount.h"

using namespace std;

BankAccount::BankAccount()
{
	acntNum = 0;
	balance = 0;
	customerName = "";
}

void BankAccount::setName(string name)
{
	customerName = name;
}

void BankAccount::setAcntNum(int num)
{
	acntNum = num;
}
int BankAccount::getAcntNum()
{
	return acntNum;
}
double BankAccount::getBalance()
{
	return balance;
}
void BankAccount::deposit(double depositAmt)
{
	balance = balance + depositAmt;
}
void BankAccount::withdraw(double withdrawAmt) //TODO add error message if insufficient funds
{
	balance = balance - withdrawAmt;
}
void BankAccount::printInfo()
{
	cout<<"Name: "<<customerName<<endl
		<<"Account number: "<<acntNum<<endl
		<<"Balance: $"<<balance<<endl;
		
}