//SavingsAccount.h programming assignment 3
//header file for programming assignment 3
//Stefan Theard
//6/25/2013
#include "BankAccount.h"

class SavingsAccount : public BankAccount
{
private:
	double interestRate, interestAccrued;
	
public:
	SavingsAccount();
	void setRate(int newRate); //1
	double getRate(); //2
	void postInterest(); //3
	void printSavingsInfo(); //4
};