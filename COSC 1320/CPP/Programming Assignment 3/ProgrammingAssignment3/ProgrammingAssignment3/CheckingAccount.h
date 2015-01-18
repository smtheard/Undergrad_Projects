//CheckingAccount.h programming assignment 3
//header file for programming assignment 3
//Stefan Theard
//6/25/2013
#ifndef CheckingAccount_H
#define CheckingAccount_H
#include "BankAccount.h"

class CheckingAccount : public BankAccount
{
private:
	double interestRate, interestAccrued, minBalance, serviceCharges, newCharge;
	bool verifyBal();							//8
	void serviceCharge();						//12


public:
	CheckingAccount();
	void setRate(int newRate);					//1
	double getRate();							//2
	void setMinBalance(double newMin);			//3
	double getMinBalance();						//4
	void setSserviceCharges(double newCharges); //5
	double getServiceCharges();				    //6
	void postInterest();						//7
	void writeCheck(double checkAmt);			//9
	void withdraw(double withdrawAmt);			//10
	void printCheckingInfo();					//11

};
#endif