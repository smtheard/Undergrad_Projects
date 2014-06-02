//BankAccount.h programming assignment 3
//header file for programming assignment 3
//Stefan Theard
//6/25/2013
#ifndef BankAccount_H
#define BankAccount_H
#include <string>

using namespace std;

class BankAccount
{
protected:
	int acntNum;
	double balance;
	string customerName;

public:
	BankAccount();
	void setName(string name); //1
	void setAcntNum(int num); //2
	int getAcntNum();         //3
	double getBalance();      //4
	void deposit(double amt); //5
	void withdraw(double withdrawAmt); //6
	void printInfo();        //7
};
#endif
