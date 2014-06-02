//BankController.h programming assignment 3
//header file for programming assignment 3
//Stefan Theard
//6/25/2013
#include "BankAccount.h"
#include "BankModel.h"
class BankController
{
private:
	BankModel bankModel;
	
public:
	bool postInterest(int acntNumber);													//uc1
	void createCheckingAccount(string customerName, int acntNumber, double amount);		//uc2
	bool checkingDeposit(int acntNumber, double amount);								//uc3
	bool checkingWithdraw(int acntNumber, double amount);								//uc4
	bool writeCheck(int acntNumber, double amount);										//uc5
	bool printAccountInfo(int acntNumber);												//uc6
	void createSavingsAccount(string customerName, int acntNumber, double amount);		//uc7
	bool savingsDeposit(int acntNumber, double amount);									//uc8
	bool savingsWithdraw(int acntNumber, double amount);								//uc9
};