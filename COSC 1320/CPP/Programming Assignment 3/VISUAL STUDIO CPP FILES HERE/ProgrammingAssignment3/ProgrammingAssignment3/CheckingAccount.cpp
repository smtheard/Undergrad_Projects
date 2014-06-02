//CheckingAccount.cpp programming assignment 3
//cpp file for programming assignment 3
//Stefan Theard
//6/25/2013
#include <iostream>
#include "BankAccount.h"
#include "CheckingAccount.h"

using namespace std;

CheckingAccount::CheckingAccount()
{
	acntNum = 0;
	balance = 0;
	customerName = "";
	interestRate = 0.10;
	minBalance = 200;
	serviceCharges = 0;
	interestAccrued = 0;
	newCharge = 22;
}

void CheckingAccount::setRate(int newRate){ interestRate = newRate;}

double CheckingAccount::getRate(){ return interestRate;}

void CheckingAccount::setMinBalance(double newMin){ minBalance = newMin;}

double CheckingAccount::getMinBalance(){ return minBalance;}

void CheckingAccount::setSserviceCharges(double newCharges){ serviceCharges = newCharges;}

double CheckingAccount::getServiceCharges(){ return serviceCharges;}

void CheckingAccount::postInterest() 
{ 
	interestAccrued = interestRate*balance;
	balance = balance + interestAccrued;
}


bool CheckingAccount::verifyBal()
{
	return (balance<minBalance); //TODO : verify correctness on bool here
}

void CheckingAccount::writeCheck(double checkAmt) //TODO : figure out if writeCheck can go negative
{												 // and if it can what response is done, service charge?
	balance = balance - checkAmt;
	if(verifyBal())
		serviceCharge();
	if(balance<0)
		serviceCharge();
}

void CheckingAccount::withdraw(double withdrawAmt)
{
	if(balance>=withdrawAmt)
		balance = balance-withdrawAmt;
	else
	{
		balance = 0;
		serviceCharge();
	}
	if(verifyBal())
		serviceCharge();
}

void CheckingAccount::printCheckingInfo()
{
	printInfo();
	cout<<"Type: Checking"<<endl
		<<"Interest rate: "<<interestRate<<endl
		<<"Interest accrued: $"<<interestAccrued<<endl
		<<"Minimum balance required to avoid service fees: $"<<minBalance<<endl
		<<"Service charges: $"<<serviceCharges<<endl
		<<"Price per service charge: $"<<newCharge<<endl;
}

void CheckingAccount::serviceCharge()
{
	serviceCharges = serviceCharges + newCharge;
	balance = balance - newCharge;
}