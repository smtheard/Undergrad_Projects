//BankModelt.h programming assignment 3
//header file for programming assignment 3
//Stefan Theard
//6/25/2013
#include <string>
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
using namespace std;

class BankModel
{
private:
	CheckingAccount checkingAccount[200];
	SavingsAccount savingsAccount[200];

public:
	void createCheckingAccount(string customerName, int acntNumber, double amount);
	void createSavingsAccount(string customerName, int acntNumber, double amount);
	bool printAccountInfo(int acntNumber);
	bool postInterest(int acntNumber);
	bool checkingDeposit(int acntNumber, double amount);
	bool savingsDeposit(int acntNumber, double amount);
	bool checkingWithdraw(int acntNumber, double amount);
	bool savingsWithdraw(int acntNumber, double amount);
	bool writeCheck(int acntNumber, double amount);
};