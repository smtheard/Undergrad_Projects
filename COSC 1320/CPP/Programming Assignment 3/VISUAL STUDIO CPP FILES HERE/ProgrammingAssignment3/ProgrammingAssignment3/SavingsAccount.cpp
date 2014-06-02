//SavingsAccount.cpp programming assignment 3
//cpp file for programming assignment 3
//Stefan Theard
//6/25/2013
#include <iostream>
#include "BankAccount.h"
#include "SavingsAccount.h"

using namespace std;

SavingsAccount::SavingsAccount()
{
	interestRate = 0.10;
	interestAccrued = 0;
	balance = 0;
	customerName = "";
}

void SavingsAccount::setRate(int newRate){ 
	interestRate = newRate; 
}

double SavingsAccount::getRate(){ 
	return interestRate; 
}

void SavingsAccount::postInterest() 
{ 
	interestAccrued = interestRate*balance;
	balance = balance + interestAccrued;
}

void SavingsAccount::printSavingsInfo()
{
	printInfo();
	cout<<"Type: Savings"<<endl
		<<"Interest rate: "<<interestRate<<endl
		<<"Interest accrued: $"<<interestAccrued<<endl;
}
