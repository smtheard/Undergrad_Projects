/*
	Hello all :)
	
	Here I will present you how to use my ArgumentManager and OperationQueue.
	The ArgumentManager is a completely new written command-line argument parser, 
	and I added a feature that may make your debugging life a little bit easier.
	The OperationQueue is also a completely new script file parser. It will read and
	parse the script file for you and keep all the script functions and expressions
	very organized to use, it will be very easy to tell expressions from ordinary 
	script functions but still you have to figure out how to decompose, prioritize, 
	interpret the expressions using stacks on your own, that part I am not allowed 
	to help. If you have any questions please send email to the TAs.
	
	WARNING:
	I adopted the STL implementation of "map" and "queue" to make the parsers efficient
	and clean. However, those STL implementations are strictly prohibited to appear in 
	any other files you submit, the automated grader will gladly offer us a hand to check.
	
*/
#include <iostream>
//You have to include the following two files to use all the functionalities
#include "ArgumentManager.cpp"
#include "OperationQueue.cpp"
using namespace std;

int main(int argc, char *argv[])
{
/*
	To begin with, create an instance of ArgumentManager.
	ArgumentManager has two constructor overloads, they are:
	1. ArgumentManager(int _argc, char *argv[], char delimiter=';')
		It will take care of all the arguments passed from command-line.
	2. ArgumentManager(string rawArguments, char delimiter=';')
		When you are debugging the program, instead of initialize the manager using
		constructor #1, you can use this constructor so that you don't have to type
		the arguments every time when you want to run it in you Notepad++ or other editors.
		
	The parameter "delimiter" is semicolon by default, you don't have to specify it
	when calling the constructor if you are using the default setting.
	
	Use ArgumentManager argMgr(argc, argv); when you want to parse the argument from
	the command-line.
	Here we will use the other constructor */
	ArgumentManager argMgr("script=sample.script"); /*
	to do a simulation.*/
	
	// I overloaded the << operator of ArgumentManager in case you want to see what did the
	// parser parse. Here is an example to use the << operator:
	cout << "Here is what we got in the ArgumentManager:" << endl << argMgr << endl;
	
	// By calling argMgr.get(argumentName), you can get any argument you want.
	// If the argument your are requesting dose not exist, it will return a blank string.
	string scriptFileName = argMgr.get("script");
	//Instantiate an OperationQueue, the constructor takes only one parameter: the filename.
	OperationQueue operQueue(scriptFileName);
	
/*
	Now we are going to fetch the operations from the queue in the order they are stored
	in the script file, and in this demo program I will just simply output the information
	contained in the operation.
*/
	while(!operQueue.isEmpty())
	{
		// Fetch the operation by calling pop().
		Operation op = operQueue.pop();
		// In order to help with your debugging, I overloaded the << operator,
		// When you are trying to use the Operation object directly in cout,
		// it will output all the properties of this operation.
		cout << op << endl;
	}
	
	return 0;
}
