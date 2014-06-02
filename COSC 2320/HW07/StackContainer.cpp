#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "ListContainer.cpp"

using namespace std;

class StackNode
{
	public:
		string data;
		LinkedList *list_data;
		StackNode *next;
		
		StackNode();
};

class StackContainer
{
	public:
		StackNode *head;
		ListContainer *all_lists; //a pointer to an object of list container
		LinkedList *postfix_list;
		
		StackContainer();
		void convertToPostfix(string expression);
		void postfixCalc(string listID);
		
		//stack operations
		void push(string input);
		void push(LinkedList *list_input);
		string pop();
		LinkedList* pop_list();
		string top();
		
		//auxiliary or testing functions
		void error(string error_message);
		void output();
};

StackNode::StackNode()
{
	data = '\0';
	list_data = NULL;
	next = NULL;
}

StackContainer::StackContainer()
{
	head = NULL;
	all_lists = NULL;
	postfix_list = NULL;
}

void StackContainer::convertToPostfix(string expression)
{
	LinkedList *postfix_list = new LinkedList();
	int trigger = 0, trigger2 = 0;
	for(unsigned int i = 0; i<expression.length(); i++)
	{
		if(expression.at(i) == '+')
		{
			if(top() == "*")
			{
				postfix_list->addWord(pop(), 1);
			}
			if(top() == "+")
			{
				postfix_list->addWord(pop(), 1);
			}
			string s(1, expression.at(i));
			push(s);
		}
		else if(expression.at(i) == '*')
		{
			if(top() == "*")
			{
				postfix_list->addWord(pop(), 1);
			}
			string s(1, expression.at(i));
			push(s);
		}
		else if(expression.at(i) == '(')
		{
			string s(1, expression.at(i));
			push(s);
		}
		else if(expression.at(i) == ')')
		{
			string s;
			s = pop();
			while(s != "")
				{
					if(s == "(")
						break;
					postfix_list->addWord(s, 1);
					s = pop();
				}
		}
		else //if it is not an operator or a parenthesis, it is an operand, and should be put into the postfix_stack
		{
			//iterate through every character after a given character until an operator or parenthesis is hit
			//created to be able to accept list names of any length
			string temp(1, expression.at(i));
			if(i+1<expression.length()) //if i is not the last char
			{
				if(expression.at(i+1) != '+' && expression.at(i+1) != '*' && expression.at(i+1) != '(' && expression.at(i+1) != ')') //and i is not an operator or parenthesis
				{
					unsigned int j = i+1;
					for(j; j<expression.length(); j++) //iterate until i becomes an operator or parenthesis
					{											 //continually concatenating the letters for multi-letter list name support
						if(expression.at(j) == '+' || expression.at(j) == '*' || expression.at(j) == '(' || expression.at(j) == ')')
						{
							i = j-1;
							trigger = 1;
							break;
						}
						else
						{
							string temp2(1, expression.at(j));
							temp = temp+temp2;
							i = j-1;
							trigger = 1;
						}
					}
					if(j==expression.length())
						trigger2 = 1; //if this gets triggered the end of expression was executed, which means a break should occur below
				}
			}
			if(trigger == 1)
			{
				trigger = 0;
				postfix_list->addWord(temp, 1);
				if(trigger2 == 1)
				{
					trigger2 = 0;
					break;
				}
				continue;
			}
			
			string s(1, expression.at(i));
			postfix_list->addWord(s, 1);
		}
	}
	string str;
	str = pop();
	while(str != "") //after the end of the expression, this loop will pop anything left over in the stack
	{
		postfix_list->addWord(str, 1);
		str = pop();
	}
	//postfix_list->output();
	this->postfix_list = postfix_list;
	return;
}

void StackContainer::postfixCalc(string listID)
{
	Node* current = postfix_list->head;
	string s1, s2, itos;
	stringstream ss;
	int i = 0;
	while(current != NULL)
	{
		if(current->word == "+")
		{
			//creates a list named "union#" where # is an arbitrary iterator used to distinguish multiple unions in a single expression
			//pushes the name to the stack in order to use it for the next operation
			//However, if it is the last node in the list, it is the final operation which means the list should be instead named listID
			s1 = pop();
			s2 = pop();
			if(s1 == "" || s2 == "")
			{
				error("Stack underflow, not enough arguments for union for operation involving " +listID);
				break;
			}
			if(current->next == NULL)
			{
				all_lists->union_initialize(s1, s2, listID, "recursive");
				break;
			}
			ss << i;
			itos = ss.str();
			all_lists->union_initialize(s1, s2, "union"+itos, "recursive");
			push("union"+itos);
			i++;
			current = current->next;
			ss.str("");
			ss.clear();
			continue;
		}
		if(current->word == "*")
		{
			//creates a list named "intersection#" where # is an arbitrary iterator used to distinguish multiple intersections in a single expression
			//pushes the name to the stack in order to use it for the next operation
			//however, if it is the last node in the list, it is the final operation which means the list should be instead named listID
			s1 = pop();
			s2 = pop();
			if(s1 == "" || s2 == "")
			{
				error("Stack underflow, not enough arguments for intersection for operation involving " +listID);
				break;
			}
			if(current->next == NULL)
			{
				all_lists->intersect_initialize(s1, s2, listID, "recursive");
				break;
			}
			ss << i;
			itos = ss.str();
			all_lists->intersect_initialize(s1, s2, "intersect"+itos, "recursive");
			push("intersect"+itos);
			i++;
			current = current->next;
			ss.str("");
			ss.clear();
			continue;
		}
		
		//if not + or *, it must be an operand, and operands get pushed to stack
		push(current->word);
		current = current->next;
		i++;
	}
	
	while(pop()!=""); //clears the stack of anything left over if the expression was not legal
}

void StackContainer::push(string input)
{
	StackNode *stackNode = new StackNode();
	stackNode->data = input;
	if(head != NULL)
		stackNode->next = head;
	head = stackNode;
}

string StackContainer::pop()
{
	if(head == NULL)
	{
		return "";
	}
	StackNode *stacknode = head;
	string thedata = stacknode->data;
	head = head->next;
	free(stacknode);
	return thedata;
}

string StackContainer::top()
{
	if(head == NULL)
		return "";
	else
		return head->data;
}

void StackContainer::output()
{
	StackNode *current = head;
	while(current != NULL)
	{
		cout << current->data << endl;
		current = current->next;
	}
	return;
}

void StackContainer::error(string error_message)
 {
	ofstream fout;
	fout.open("log.txt", ios::out | ios::app);
	fout << error_message << endl;
	fout.close();
	return;
 }