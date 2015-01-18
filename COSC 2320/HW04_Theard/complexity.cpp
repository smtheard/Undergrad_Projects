#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "ArgumentManager.cpp"
#include "OperationQueue.cpp"
#include "StackContainer.cpp"

using namespace std;

long time_actual = 0;

class TimeComplexity
{
	public:
		ListContainer *all_lists; //a pointer to an object of list container which is a list of lists
		string result_filename;
		
		TimeComplexity();
		void output(string s, string op);
		void union_tracktime(string listname1, string listname2, string listname3);
		void intersection_tracktime(string listname1, string listname2, string listname3);
};

int main(int argc, char *argv[])
{
	ListContainer list_container;
	StackContainer stack_container;
	TimeComplexity time_complexity;				   //TODO: ensure that the below sharing of the same list_container does not interfere with the stack or arithmetic infix to postfix conversions.
	time_complexity.all_lists = &list_container; //gives the TimeComplexity object an address to the listContainer
	stack_container.all_lists = &list_container; //gives the stackContainer an address to the listContainer
/* 
	time_actual = 0;
	
	list_container.initialize("A", "A20.txt");
	ListNode* list = list_container.find_list("A");
	int n_hi = list_container.getN("A");
	int estimate = (n_hi*(6*n_hi))+ 9;
	cout << estimate << " ESTIMATE " << endl;
	list->list.alphabetize();
	cout << time_actual << endl;
	list->list.output();
	return 99; */
	if ( argc != 2 )
	{
		list_container.error("No file input or too many arguments, please try again");
		return -1;
	}
	ArgumentManager argMgr(argv[1]);
	string filename = argMgr.get("script");
	time_complexity.result_filename = argMgr.get("result");
	time_complexity.output("L1,L2,,,,-----,---,O(g(n)),--------,,", "");
	time_complexity.output("size,size,operation,T(n) estimate,T(n) actual,c,n0,g(n)=n^2", "append");
	
	char* fn = new char[filename.length()+1];
	strcpy(fn, filename.c_str());
	
	ifstream fin(fn);
	if(fin.fail())
	{
		list_container.error("Failure to open script file "+filename+" exiting program...");
		return -1;
	}
	
	list_container.error("||||||||||||| Start log for script file "+filename+" |||||||||||||");
	
	OperationQueue opQueue(filename);
	
	while(!opQueue.isEmpty())
	{
		Operation op = opQueue.pop();
		//cout << op << endl;
		if(op.isExpression())	//if true, operation is an expression that needs to be evaluated
		{
			stack_container.convertToPostfix(op.getExpression()); //convert infix to postfix
			stack_container.postfixCalc(op.getName()); //calculte the postfix expression and perform the operations
		}
		else if(op.getName() == "write" || op.getName() == "read")			//if false, the operation could be a simple read or write
		{
			if(op.getName() == "write")
			{	
				if(op.parameterCount() == 2)	//this means there is no 'forward' or 'reverse' specification in which we will just assume forward
				{
					list_container.writeForward(op.getParameter(0), op.getParameter(1));
				}
				else if(op.getParameter(2) == "forward")
				{
					list_container.writeForward(op.getParameter(0), op.getParameter(1));
				}
				else if(op.getParameter(2) == "reverse")
				{	
					list_container.writeReverse(op.getParameter(0), op.getParameter(1));
				}
				else
				{
					list_container.writeForward(op.getParameter(0), op.getParameter(1));
				}
				continue;
			}
			
			if(op.getName() == "read")
			{
				list_container.initialize(op.getParameter(0), op.getParameter(1));
				continue;
			}
		}
		else if(op.getName() == "union" || op.getName() == "intersection") //if not expression or read/write, it must be a union or intersection command
		{
			if(op.getName() == "union")
			{
				// call time complex func, and union here using op.getParameter(0) 1 and 2
				time_complexity.union_tracktime(op.getParameter(0), op.getParameter(1), op.getParameter(2));
				continue;
			}
			else if(op.getName() == "intersection")
			{
				// call time complex func, and intersection here using op.getParameter(0) 1 and 2
				time_complexity.intersection_tracktime(op.getParameter(0), op.getParameter(1), op.getParameter(2));
				continue;
			}
		}
		else
			list_container.error("operation is neither an expression, read/write, or union/intersection and therefore invalid");
	}

	//list_container.armageddon(); //deallocates all memory taken by the various lists and crashes the program currently, after merge was implemented in union_func_iterative
	list_container.error("||||||||||||| End log for script file "+filename+" |||||||||||||");
	return 99;
}

TimeComplexity::TimeComplexity()
{
	all_lists = NULL;
	result_filename = "";
}

void TimeComplexity::output(string s, string op)
{
	ofstream fout;
	if(op == "append")
		fout.open(result_filename.c_str(), ios::out | ios::app);
	else
		fout.open(result_filename.c_str());
	fout << s << endl;
	fout.close();
	return;
}

void TimeComplexity::union_tracktime(string listname1, string listname2, string listname3)
{
	time_actual = 0;
	long n_1 = all_lists->getN(listname2);
	long n_2 = all_lists->getN(listname3);
	long n_low, n_hi;
	if(n_1 > n_2)
	{
		n_low = n_2;
		n_hi = n_1;
	}
	else
	{
		n_low = n_1;
		n_hi = n_2;
	}
	//union's algorithm  5*(n_low + n_low*n_low+ n_hi*n_hi) how I got 5 is in the README
	long tc_estimate = 5*(n_low + n_low*n_low+ n_hi*n_hi);
	long c = 8;
	long upper_bound = c*((n_hi*n_hi) + (n_low*n_low)); // n^2 is the upper bound or O(n^2), since bubble sort is used to alphabetize
	
	all_lists->union_initialize(listname3, listname2, listname1, "iterative"); // calling the actual union function to calculate the TIME_ACTUAL
	
	stringstream ss; //outputting all data in CSV format
	ss<<n_1<<","<<n_2<<","<<"union,"<<tc_estimate<<","<<time_actual<<","<<c<<",64,"<<upper_bound;
	string result = ss.str();
	output(result, "append");
	return;
}

void TimeComplexity::intersection_tracktime(string listname1, string listname2, string listname3)
{
	time_actual = 0;
	long n_1 = all_lists->getN(listname2);
	long n_2 = all_lists->getN(listname3);
	long n_low, n_hi;
	string greater_list, lesser_list;

	if(n_1 > n_2)
	{
		greater_list = listname2;
		lesser_list = listname3;
		n_low = n_2;
		n_hi = n_1;
	}
	else
	{
		greater_list = listname3;
		lesser_list = listname2;
		n_low = n_1;
		n_hi = n_2;
	}
	
	//intersection's algorithm  3.95*(n_low*n_low + n_hi*n_hi + n_low*n_hi + n_low) how I got 3.95 is in the README
	long tc_estimate = 3.95*(n_low*n_low + n_hi*n_hi + n_low*n_hi + n_low);
	long c = 8;
	long upper_bound = c*((n_hi*n_hi) + (n_low*n_low)); // n^2 is the upper bound or O(n^2), since bubble sort is used to alphabetize times a constant c for the true upper bound

	all_lists->intersect_initialize(greater_list, lesser_list, listname1, "iterative"); // calling the actual intersection function to calculate the TIME_ACTUAL
	
	stringstream ss; //outputting all data in CSV format
	ss<<n_1<<","<<n_2<<","<<"intersection,"<<tc_estimate<<","<<time_actual<<","<<c<<",64,"<<upper_bound;
	string result = ss.str();
	output(result, "append");
	return;
}