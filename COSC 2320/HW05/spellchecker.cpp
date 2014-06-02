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
#include "TreeContainer.cpp"

using namespace std;

int main(int argc, char *argv[])
{
	ListContainer list_container;
	StackContainer stack_container;
	stack_container.all_lists = &list_container;
	TreeContainer tree_container;
	tree_container.all_lists = &list_container;

	if ( argc != 2 )
	{
		list_container.error("No file input or too many arguments, please try again");
		return -1;
	}
	
	ArgumentManager argMgr(argv[1]);
	string filename = argMgr.get("script");
	string dict_filename = argMgr.get("dictionary"); 

	char* fn = new char[filename.length()+1];
	strcpy(fn, filename.c_str());
	
	list_container.initialize("dictionary", dict_filename); //insert the dictionary into a list
	ListNode* dictionary_list = list_container.find_list("dictionary");
	tree_container.initiate_tree(dictionary_list->list);
	//tree_container.printLevelOrder(tree_container.root, 6);
	
	
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
					list_container.writeForward(op.getParameter(0), op.getParameter(1), "iterative");
				}
				else if(op.getParameter(2) == "forward")
				{
					list_container.writeForward(op.getParameter(0), op.getParameter(1), "iterative");
				}
				else if(op.getParameter(2) == "reverse")
				{
					list_container.writeReverse(op.getParameter(0), op.getParameter(1), "iterative");
				}
				else
				{
					list_container.writeForward(op.getParameter(0), op.getParameter(1), "iterative");
				}
				continue;
			}
			
			if(op.getName() == "read")
			{
				list_container.initialize(op.getParameter(0), op.getParameter(1));
				continue;
			}
		}
		else if(op.getName() == "union" || op.getName() == "intersection" || op.getName() == "check") //if not expression or read/write, it must be a union or intersection command
		{
			if(op.getName() == "union")
			{
				//call union func from list container with op.getParameter(0) 1 and 2
				list_container.union_initialize(op.getParameter(0), op.getParameter(1), op.getParameter(2), "recursive");
				//continue;
			}
			else if(op.getName() == "intersection")
			{
				//call intersection func from list container with op.getParameter(0) 1 and 2
				list_container.intersect_initialize(op.getParameter(0), op.getParameter(1), op.getParameter(2), "recursive");
				//continue;
			}
			else if(op.getName() == "check")
			{
				//call function that checks the op.getParameter(1) list with the dictionary passed earlier and then stores
				//the misspelled words or words that aren't in the dictionary to op.getParameter(0).
				tree_container.check(op.getParameter(0), op.getParameter(1));
			}
		}
		else
			list_container.error("operation is neither an expression, read/write, or union/intersection and therefore invalid");
	}

	list_container.armageddon(); //deallocates all memory taken by the various lists and crashes the program currently, after merge was implemented in union_func_iterative
	list_container.error("||||||||||||| End log for script file "+filename+" |||||||||||||");
	return 99;
}




