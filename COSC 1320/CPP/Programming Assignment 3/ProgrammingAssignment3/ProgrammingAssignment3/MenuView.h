//MenuView.h programming assignment 3
//header file for programming assignment 3
//Stefan Theard
//6/25/2013
#include <string>
using namespace std;
class MenuView
{
public:
	int userChoiceMenu();															//1
	int customerMenu();																//2
	int bankEmployeeMenu();															//3
	void getCheckInfo(string& customerName, int& acntNumber, double& amount);		//4
	void getWithdrawInfo(string& customerName, int& acntNumber, double& amount);	//5
	void getDepositInfo(int& acntNumber, double& amount);							//6
	void getCustomerInfo(string& customerName, int& acntNumber, double& amount);	//7
	void getAccountNumInfo(int& acntNumber);										//8
	void accountNotFound();															//9
private:
	int userChoice;
};
