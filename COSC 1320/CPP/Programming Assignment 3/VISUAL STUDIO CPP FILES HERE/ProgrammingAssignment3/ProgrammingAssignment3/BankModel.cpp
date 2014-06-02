//BankModel.cpp programming assignment 3
//cpp file for programming assignment 3
//Stefan Theard
//6/25/2013
#include <string>
#include "BankModel.h"
using namespace std;

void BankModel::createCheckingAccount(string customerName, int acntNumber, double amount)
{
	for(int i = 0; i<200; i++)
	{
		if(checkingAccount[i].getAcntNum() == 0)
		{
			checkingAccount[i].setAcntNum(acntNumber);
			checkingAccount[i].setName(customerName);
			checkingAccount[i].deposit(amount);
			return;
		}
	}
}

void BankModel::createSavingsAccount(string customerName, int acntNumber, double amount)
{
	for(int i = 0; i<200; i++)
	{
		if(savingsAccount[i].getAcntNum() == 0)
		{
			savingsAccount[i].setAcntNum(acntNumber);
			savingsAccount[i].setName(customerName);
			savingsAccount[i].deposit(amount);
			return;
		}
	}
}

bool BankModel::printAccountInfo(int acntNumber)
{
	int i;
	for(i = 0; i<200; i++)
	{
		if(savingsAccount[i].getAcntNum() == acntNumber)
			savingsAccount[i].printSavingsInfo();
		if(checkingAccount[i].getAcntNum() == acntNumber)
			checkingAccount[i].printCheckingInfo();
	}
	if(i == 199)
		return false;
	return true;
}

bool BankModel::postInterest(int acntNumber)
{
	int i;
	for(i = 0; i<200; i++)
	{
		if(savingsAccount[i].getAcntNum() == acntNumber)
			savingsAccount[i].postInterest();
		if(checkingAccount[i].getAcntNum() == acntNumber)
			checkingAccount[i].postInterest();
	}
	if(i == 199)
		return false;
	return true;
}

bool BankModel::checkingDeposit(int acntNumber, double amount)
{
	for(int i = 0; i<200; i++)
	{
		if(checkingAccount[i].getAcntNum() == acntNumber)
		{
			checkingAccount[i].deposit(amount);
			return true;
		}
	}
	return false;
}

bool BankModel::savingsDeposit(int acntNumber, double amount)
{
	for(int i = 0; i<200; i++)
	{
		if(savingsAccount[i].getAcntNum() == acntNumber)
		{
			savingsAccount[i].deposit(amount);
			return true;
		}
	}
	return false;
}

bool BankModel::checkingWithdraw(int acntNumber, double amount)
{
	for(int i = 0; i<200; i++)
	{
		if(checkingAccount[i].getAcntNum() == acntNumber)
		{
			checkingAccount[i].withdraw(amount);
			return true;
		}
	}
	return false;
}

bool BankModel::savingsWithdraw(int acntNumber, double amount)
{
	for(int i = 0; i<200; i++)
	{
		if(savingsAccount[i].getAcntNum() == acntNumber)
		{
			savingsAccount[i].withdraw(amount);
			return true;
		}
	}
	return false;
}

bool BankModel::writeCheck(int acntNumber, double amount)
{
	for(int i = 0; i<200; i++)
	{
		if(checkingAccount[i].getAcntNum() == acntNumber)
		{
			checkingAccount[i].writeCheck(amount);
			return true;
		}
	}
	return false;
}