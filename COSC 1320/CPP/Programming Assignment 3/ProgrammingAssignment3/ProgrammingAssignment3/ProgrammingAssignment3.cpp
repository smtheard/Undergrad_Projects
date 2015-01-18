//ProgrammingAssignment3.cpp programming assignment 3
//cpp file for programming assignment 3
//Stefan Theard
//6/25/2013
#include <iostream>
#include <string>
#include "BankAccount.h"
#include "BankController.h"
#include "MenuView.h"

using namespace std;

int main()
{
	int acntNumber, userChoice;
	double amount;
	string customerName;

	MenuView view;
	BankController controller = BankController();

	do{
	userChoice = -1;
	acntNumber = 0;
	customerName = "";
	userChoice = view.userChoiceMenu();
	if(userChoice == 1)
	{
		userChoice = view.customerMenu();
		if(userChoice == 1)
		{
			view.getCheckInfo(customerName, acntNumber, amount);
			if(!controller.writeCheck(acntNumber, amount))
				view.accountNotFound();	
		}
		else if(userChoice == 2)
		{
			view.getWithdrawInfo(customerName, acntNumber, amount);
			if(!controller.checkingWithdraw(acntNumber, amount))
				view.accountNotFound();
		}
		else if(userChoice == 3)
		{
			view.getDepositInfo(acntNumber, amount);
			if(!controller.savingsWithdraw(acntNumber, amount))
				view.accountNotFound();
		}
		else if(userChoice == 4)
		{
			view.getDepositInfo(acntNumber, amount);
			if(!controller.checkingDeposit(acntNumber, amount))
				view.accountNotFound();
		}
		else if(userChoice == 5)
		{
			view.getDepositInfo(acntNumber, amount);
			if(!controller.savingsDeposit(acntNumber, amount))
				view.accountNotFound();
		}
	}
	else if(userChoice == 2)
	{
		userChoice = view.bankEmployeeMenu();
		if(userChoice == 1)
		{
			view.getCustomerInfo(customerName, acntNumber, amount);
			controller.createCheckingAccount(customerName, acntNumber, amount);
		}
		else if(userChoice == 2)
		{
			view.getCustomerInfo(customerName, acntNumber, amount);
			controller.createSavingsAccount(customerName, acntNumber, amount);
		}
		else if(userChoice == 3)
		{
			view.getAccountNumInfo(acntNumber);
			if(!controller.postInterest(acntNumber))
				view.accountNotFound();
		}
	}
	else if(userChoice == 3)
	{
		view.getAccountNumInfo(acntNumber);
		controller.printAccountInfo(acntNumber);
	}
	}while(userChoice != 9);

	return 0;
}
