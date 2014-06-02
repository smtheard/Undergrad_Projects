//BankController.cpp programming assignment 3
//cpp file for programming assignment 3
//Stefan Theard
//6/25/2013
#include "BankController.h"

void BankController::createCheckingAccount(string customerName, int acntNumber, double amount)
{
	bankModel.createCheckingAccount(customerName, acntNumber, amount);
}

void BankController::createSavingsAccount(string customerName, int acntNumber, double amount)
{
	bankModel.createSavingsAccount(customerName, acntNumber, amount);
}

bool BankController::printAccountInfo(int acntNumber)
{
	return bankModel.printAccountInfo(acntNumber);
}

bool BankController::postInterest(int acntNumber)
{
	return bankModel.postInterest(acntNumber);
}

bool BankController::checkingDeposit(int acntNumber, double amount)
{
	return bankModel.checkingDeposit(acntNumber, amount);
}

bool BankController::savingsDeposit(int acntNumber, double amount)
{
	return bankModel.savingsDeposit(acntNumber, amount);
}

bool BankController::checkingWithdraw(int acntNumber, double amount)
{
	return bankModel.checkingWithdraw(acntNumber, amount);
}

bool BankController::savingsWithdraw(int acntNumber, double amount)
{
	return bankModel.savingsWithdraw(acntNumber, amount);
}

bool BankController::writeCheck(int acntNumber,double amount)
{
	return bankModel.writeCheck(acntNumber, amount);
}